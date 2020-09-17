

struct scull_listitem {
	struct scull_dev device;
	dev_t key;
	struct list_head list;
}

/* The list of devices and a lock to protect it */
static LIST_HEAD(scull_c_list);
static spinlock_t scull_c_lock = SPIN_LOCK_UNLOCKED;

static struct scull_dev *scull_c_lookfor_device(dev_t key)
{
	struct scull_listitem *lptr;

	list_for_each_entry(lptr, &scull_c_list, list) {
		if (lptr->key == key)
			return &(lptr->device);
	}

	lptr = kmalloc(sizeof(struct scull_listitem), GFP_KERNEL);
	if (!lptr)
		return NULL;

	memset(lptr, 0, sizeof(struct scull_listitem));
	lptr->key = key;
	scull_trim(&(lptr->device));
	init_MUTEX(&(lptr->device.sem));

	list_add(&lptr->list, &scull_c_list);

	return &(lptr->device);
}

static int scull_c_open(struct inode *inode, struct file *filp)
{
	struct scull_dev *dev;
	dev_t key;

	if (!current->signal->tty) {
		pr_info("Process %s has no ctl tty\n", current->comm);
		return -EINVAL;
	}

	key = tty_devnum(current->signal->tty);

	spin_lock(&scull_c_lock);
	dev = scull_c_lookfor_device(key);
	spin_unlock(&scull_c_lock);

	if (!dev)
		return -ENOMEM;


}
