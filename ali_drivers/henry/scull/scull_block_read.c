

struct scull_pipe {
	wait_queue_head_t inq, outq;
	char *buffer, *end;
	int buffersize;
	char *rp, *wp;
	int nreaders, nwriters;
	struct fasync_struct *async_queue;
	struct semaphore sem;
	struct cdev cdev;
};

static ssize_t scull_p_read(struct file *filp, char __user *buf,
		size_t count, loff_t *f_pos)
{
	struct scull_pipe *dev = filp->private_data;

	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	while (dev->rp == dev->wp) {	/* there is nothing to read */		
		up(&dev->sem);

		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;

		pr_info("%s reading: going to sleep\n", current->comm);

		if (wait_event_interruptible(dev->inq, dev->rp != dev->wp))
			return -ERESTARTSYS;	/* signal: noitce fs layer to handle it */

		/* otherwise, lock the semaphore */
		if (down_interruptible(&dev->sem))
			return -ERESTARTSYS;
	}

	/* the data is already */
	if (dev->wp > dev->rp)
		count = min(count, (size_t)(dev->wp - dev->rp));
	else	/* the writer pointer has wrapped and fill up to (read_ptr - 1). */
		count = min(count, (size_t)(dev->end - dev->rp));

	if (copy_to_user(buf, dev->rp, count)) {
		up(&dev->sem);
		return -EFAULT;
	}

	dev->rp += count;
	if (dev->rp == dev->end)	/* wrapped */
		dev->rp = dev->buffer;
	up(&dev->sem);

	/* wake up all writer and return */
	wake_up_interruptible(&dev->outq);
	pr_info("%s did read %li bytes\n", current->comm, (long)count);

	return count;
}

static int spacefree(struct scull_pipe *dev)
{
	if (dev->rp == dev->wp)
		return dev->buffersize - 1;

	return ((dev->rp + dev->buffersize - dev->wp) % dev->buffersize) - 1;
}

/* Wait for space for writing: 
 * Caller must hold device semaphore.
 * On error, the semaphore will be released before returning.
 */
static scull_getwritespace(struct scull_pipe *dev, struct file *filp)
{
	while (!spacefree(dev)) {	/* if it is full then sleep again */

		DEFINE_WAIT(wait);

		up(&dev->sem);
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;

		pr_info("%s writing: going to sleep\n", current->comm);
		prepare_to_wait(&dev->outq, &wait, TASK_INTERRUPTIBLE);
		
		if (!spacefree(dev))
			schedule();

		finish_wait(&dev->outq, &wait);
		if (signal_pending(current))	/* estimate the signal execption */
			return -ERESTARTSYS;

		if (down_interruptible(&dev->sem))
			return -ERESTARTSYS;
	}

	return 0;
}

static ssize_t scull_p_write(struct file *filp, const char __user *buf,
		size_t count, loff_t *f_pos)
{
	struct scull_pipe *dev = filp->private_data;
	int result;
	
	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	/* make sure there is space to write */
	result = scull_getwritespace(dev, filp);
	if (result)
		return result;	/* scull_getwritespace would up sem */

	/* there is space to write and receive data */
	count = min(count, (size_t)spacefree(dev));
	if (dev->wp >= dev->rp)
		count = min(count, (size_t)(dev->end - dev->wp));
	else	/* wrapped */
		count = min(count, (size_t)(dev->rp - dev->wp - 1));

	pr_info("Going to accept %d bytes to %p from %p\n", count, dev->wp, buf);

	if (copy_from_user(dev->wp, buf, count)) {
		up(&dev->sem);
		return -EFAULT;
	}

	dev->wp += count;
	if (dev->wp == dev->end)
		dev->wp = dev->buffer;
	up(&dev->sem);
	
	wake_up_interruptible(&dev->inq);	/* wake up reader queue */

	/* notice async readers */
	if (dev->async_queue)
		kill_fasync(&dev->async_queue, SIGIO, POLL_IN);

	pr_info("%s did write %d bytes\n", current->comm, count);
	return count;
}

/*  */
static unsigned int scull_p_poll(struct file *filp, poll_table *wait)
{
	struct scull_pipe *dev = filp->private_data;
	unsigned int mask = 0;
	
	/* 
	*	The buffer is circular; It is considered full if "wp" is right behind "rp"
	*	and empty if the two are equal.
	*/
	down(&dev->sem);

	/*
	*	add current thread into wait queue
	*	or would sleep until timeout in do_poll.
	*/
	poll_wait(filp, &dev->inq, wait);
	poll_wait(filp, &dev->outq, wait);

	if (dev->rp != dev->wp)
		mask |= POLLIN | POLLRDNORM;	/* readable */
	if (spacefree(dev))
		mask |= POLLOUT | POLLWRNORM;	/* writable */

	up(&dev->sem);

	return mask;
}

static int scull_p_fasync(int fd, struct file *filp, int on)
{
	struct scull_pipe *dev = filp->private_data;

	return fasync_helper(fd, filp, on, &dev->async_queue);
}

static int scull_p_close(struct inode *pnode, struct file *filp)
{
	struct scull_pipe *dev = filp->private_data;

	/* release from the async notice list */
	fasync_helper(-1, filp, 0, &dev->async_queue);

	return 0;
}

static loff_t scull_llseek(struct file *filp, loff_t offset, int whence)
{
	struct scull_pipe *dev = filp->private_data;
	loff_t newpos;
	
	switch (whence) {
	case SEEK_SET:
		newpos = offset;
		break;

	case SEEK_CUR:
		newpos = filp->f_pos + offset;
		break;

	case SEEK_END:
		newpos = dev->buffersize + offset;
		break;

	default:
		return -EINVAL;
	}

	if (newpos < 0)
		return -EINVAL;

	filp->f_pos = newpos;
	return newpos;
}
