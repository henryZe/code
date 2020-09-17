

static struct scull_pipe scull_s_device;
static atomic_t scull_s_available = ATOMIC_INIT(1);

static int scull_s_open(struct inode *pnode, struct file *filp)
{
	struct scull_pipe *dev = &scull_s_device;

	if (!atomic_dec_and_test(&scull_s_available)) {
		atomic_inc(&scull_s_available);
		return -EBUSY;
	}

	filp->private_data = dev;

	return 0;
}

static int scull_s_close(struct inode *pnode, struct file *filp)
{
	atomic_inc(&scull_s_available);
	return 0;
}
