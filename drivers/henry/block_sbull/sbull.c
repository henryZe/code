#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>	/* printk() */
#include <linux/slab.h>		/* kmalloc() */
#include <linux/fs.h>		/* everything... */
#include <linux/vmalloc.h>
#include <linux/genhd.h>
#include <linux/blkdev.h>
#include <linux/hdreg.h>	/* HDIO_GETGEO */

#define SBULL_MINORS	16

/*
 * We can tweak our hardware sector size, but the kernel talks to us
 * in terms of small sectors, always.
 */
#define KERNEL_SECTOR_SIZE	512

#define INVALIDATE_DELAY	(20 * HZ)

static int sbull_major = 0;
module_param(sbull_major, int, 0);
static int ndevices = 4;
module_param(ndevices, int, 0);
static int nsectors = 1024;	/* How big the driver is */
module_param(nsectors, int, 0);
static int hardsect_size = 512;
module_param(hardsect_size, int, 0);
enum {
	RM_SIMPLE  = 0,	/* The extra-simple request function */
	RM_FULL    = 1,	/* The full-blown version */
	RM_NOQUEUE = 2,	/* Use make_request */
};
static int request_mode = RM_SIMPLE;
module_param(request_mode, int, 0);

struct sbull_dev {
	int size;                       /* Device size in sectors */
	u8 *data;                       /* The data array */
	short users;                    /* How many users */
	short media_change;             /* Flag a media change? */
	spinlock_t lock;                /* For mutual exclusion */
	struct request_queue *queue;    /* The device request queue */
	struct gendisk *gd;             /* The gendisk structure */
	struct timer_list timer;        /* For simulated media changes */
};

static struct sbull_dev *Devices = NULL;

static int sbull_open(struct block_device *bdev, fmode_t mode)
{
	struct sbull_dev *dev = (struct sbull_dev *)bdev->bd_disk->private_data;

	del_timer_sync(&dev->timer);
	spin_lock(&dev->lock);
	if (!dev->users) 
		check_disk_change(bdev);
	dev->users++;
	spin_unlock(&dev->lock);
	return 0;
}

static void sbull_release(struct gendisk *disk, fmode_t mode)
{
	struct sbull_dev *dev = (struct sbull_dev *)disk->private_data;

	spin_lock(&dev->lock);
	dev->users--;

	if (!dev->users) {
		dev->timer.expires = jiffies + INVALIDATE_DELAY;
		add_timer(&dev->timer);
	}
	spin_unlock(&dev->lock);
}

/* Look for a (simulated) media change. */
int sbull_media_changed(struct gendisk *gd)
{
	struct sbull_dev *dev = gd->private_data;
	
	return dev->media_change;
}

/*
 * Revalidate.  WE DO NOT TAKE THE LOCK HERE, for fear of deadlocking
 * with open.  That needs to be reevaluated.
 */
int sbull_revalidate(struct gendisk *gd)
{
	struct sbull_dev *dev = gd->private_data;
	
	if (dev->media_change) {
		dev->media_change = 0;
		memset (dev->data, 0, dev->size);
	}
	return 0;
}

/*
 * The ioctl() implementation
 */
int sbull_ioctl(struct block_device *bdev, fmode_t mode, unsigned cmd, unsigned long arg)
{
	long size;
	struct hd_geometry geo;
	struct sbull_dev *dev = (struct sbull_dev *)bdev->bd_disk->private_data;

	switch(cmd) {
	case HDIO_GETGEO:
        /*
		 * Get geometry: since we are a virtual device, we have to make
		 * up something plausible.  So we claim 16 sectors, four heads,
		 * and calculate the corresponding number of cylinders.  We set the
		 * start of data at sector four.
		 */
		size = dev->size * (hardsect_size / KERNEL_SECTOR_SIZE);
		geo.cylinders = (size & ~0x3f) >> 6;
		geo.heads = 4;
		geo.sectors = 16;
		geo.start = 4;
		if (copy_to_user((void __user *)arg, &geo, sizeof(geo)))
			return -EFAULT;

		return 0;
	}

	return -ENOTTY; /* unknown command */
}

const struct block_device_operations sbull_ops = {
	.owner = THIS_MODULE,
	.open = sbull_open,
	.release = sbull_release,
	.media_changed = sbull_media_changed,
	.revalidate_disk = sbull_revalidate,
	.ioctl = sbull_ioctl,
};

/*
 * The "invalidate" function runs out of the device timer;
 * it sets a flag to simulate the removal of the media.
 */
void sbull_invalidate(unsigned long ldev)
{
	struct sbull_dev *dev = (struct sbull_dev *)ldev;

	spin_lock(&dev->lock);

	if (dev->users || !dev->data)
		pr_info("sbull: timer sanity check failed\n");
	else
		dev->media_change = 1;

	spin_unlock(&dev->lock);
}

/* Handle an I/O request. */
static void sbull_transfer(struct sbull_dev *dev, unsigned long sector,
		unsigned long nbytes, char *buffer, int write)
{
	unsigned long offset = sector * KERNEL_SECTOR_SIZE;

	if ((offset + nbytes) > dev->size) {
		pr_info("Beyond-end write (%ld %ld)\n", offset, nbytes);
		return;
	}

	if (write)
		memcpy(dev->data + offset, buffer, nbytes);
	else
		memcpy(buffer, dev->data + offset, nbytes);
}

/* The simple form of the request function. */
static void sbull_request(struct request_queue *q)
{
	struct request *req;

	while ((req = blk_fetch_request(q)) != NULL) {
		struct sbull_dev *dev = req->rq_disk->private_data;
    	pr_info("Req dev %d dir %d, sector %ld (start: %ld) data_len %d\n",
			dev - Devices, rq_data_dir(req), blk_rq_pos(req), blk_rq_pos(req) << 9, blk_rq_bytes(req));
		sbull_transfer(dev, blk_rq_pos(req), blk_rq_bytes(req),
				req->buffer, rq_data_dir(req));
		//blk_finish_request(req, 1);
	}
}

/* Set up the internal device. */
static void setup_device(struct sbull_dev *dev, int which)
{
	memset(dev, 0, sizeof(struct sbull_dev));
	dev->size = nsectors * hardsect_size;
	dev->data = vmalloc(dev->size);
	if (dev->data == NULL) {
		pr_info("vmalloc failure.\n");
		return;
	}

	spin_lock_init(&dev->lock);

	/* The timer which "invalidates" the device. */
	init_timer(&dev->timer);
	dev->timer.data = (unsigned long)dev;
	dev->timer.function = sbull_invalidate;

	/*
	 * The I/O queue, depending on whether we are using our own
	 * make_request function or not.
	 */
	switch (request_mode) {
#if 0
    case RM_NOQUEUE:
		dev->queue = blk_alloc_queue(GFP_KERNEL);
		if (dev->queue == NULL)
			goto out_vfree;
		blk_queue_make_request(dev->queue, sbull_make_request);
		break;

    case RM_FULL:
		dev->queue = blk_init_queue(sbull_full_request, &dev->lock);
		if (dev->queue == NULL)
			goto out_vfree;
		break;
#endif
	default:
		pr_info("Bad request mode %d, using simple\n", request_mode);
		/* fall into RM_SIMPLE */

    case RM_SIMPLE:
		dev->queue = blk_init_queue(sbull_request, &dev->lock);
		if (dev->queue == NULL)
			goto out_vfree;
		break;
	}
	/* blk_queue_hardsect_size(dev->queue, hardsect_size); */
	dev->queue->queuedata = dev;

	/* And the gendisk structure. */
	dev->gd = alloc_disk(SBULL_MINORS);
	if (!dev->gd) {
		pr_info("alloc_disk failure\n");
		goto out_vfree;
	}
	dev->gd->major = sbull_major;
	dev->gd->first_minor = which * SBULL_MINORS;
	dev->gd->fops = &sbull_ops;
	dev->gd->queue = dev->queue;
	dev->gd->private_data = dev;
	snprintf (dev->gd->disk_name, 32, "sbull%c", which + 'a');
	set_capacity(dev->gd, nsectors * (hardsect_size / KERNEL_SECTOR_SIZE));
	add_disk(dev->gd);

	return;

out_vfree:
	if (dev->data)
		vfree(dev->data);
}

static int __init sbull_init(void)
{
	int i;

	/* gain the device major number */
	sbull_major = register_blkdev(sbull_major, "sbull");
	if (sbull_major <= 0) {
		pr_info("sbull: unable to get major number\n");
		return -EBUSY;
	}

	Devices = kmalloc(ndevices * sizeof(struct sbull_dev), GFP_KERNEL);
	if (Devices == NULL)
		goto out_unregister;

	for (i = 0; i < ndevices; i++) 
		setup_device(Devices + i, i);

	return 0;

out_unregister:
	unregister_blkdev(sbull_major, "sbd");
	return -ENOMEM;
}

static void sbull_exit(void)
{
	
}

module_init(sbull_init);
module_exit(sbull_exit);
