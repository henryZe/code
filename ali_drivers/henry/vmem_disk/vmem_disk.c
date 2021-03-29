#include <linux/spinlock.h>
#include <linux/module.h>
#include <linux/vmalloc.h>
#include <linux/blkdev.h>
#include <linux/hdreg.h>

#include "vmem_disk.h"

static int vmem_disk_major;

static int request_mode;
module_param(request_mode, int, S_IRUGO);

struct vmem_disk_dev {
	unsigned long size;
	void *data;
	spinlock_t lock;
	struct request_queue *queue;
	struct gendisk *gd;
};

struct vmem_disk_dev *devices;

/* complete an operation on hardware */
static void vmem_disk_transfer(struct vmem_disk_dev *dev, sector_t sector, unsigned long nsect, char *buffer, int write)
{
	unsigned long offset = sector * KERNEL_SECTOR_SIZE;
	unsigned long nbytes = nsect * KERNEL_SECTOR_SIZE;

	if ((offset + nbytes) > dev->size) {
		printk("beyond end write (%ld %ld)\n", offset, nbytes);
		return;
	}

	if (write)
		memcpy(dev->data + offset, buffer, nbytes);
	else
		memcpy(buffer, dev->data + offset, nbytes);
}

/* complete operations for each bio */
static int vmem_disk_xfer_bio(struct vmem_disk_dev *dev, struct bio *bio)
{
	struct bio_vec *bvec;
	unsigned short bi_idx;
	sector_t sector = bio->bi_sector;
	char *buffer;

	bio_for_each_segment(bvec, bio, bi_idx) {
		buffer = __bio_kmap_atomic(bio, bi_idx);
		vmem_disk_transfer(dev, sector, bio_cur_bytes(bio) >> 9, buffer, bio_data_dir(bio) == WRITE);
		sector += bio_cur_bytes(bio) >> 9;
		__bio_kunmap_atomic(buffer);
	}

	return 0;
}

static void vmem_disk_make_request(struct request_queue *q, struct bio *bio)
{
	struct vmem_disk_dev *dev = q->queuedata;

	bio_endio(bio, vmem_disk_xfer_bio(dev, bio));
}

static int vmem_disk_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	long size;
	struct vmem_disk_dev *dev = bdev->bd_disk->private_data;

	size = dev->size * (HWSECTOR_SIZE/KERNEL_SECTOR_SIZE);
	geo->cylinders = (size & ~0x3f) >> 6;
	geo->heads = 4;
	geo->sectors = 16;
	geo->start = 4;

	return 0;
}

static struct block_device_operations vmem_disk_ops = {
	.getgeo = vmem_disk_getgeo,
};

static void vmem_disk_request(struct request_queue *q)
{
	struct request *req;
	struct bio *bio;

	while ((req = blk_peek_request(q)) != NULL) {
		struct vmem_disk_dev *dev = req->rq_disk->private_data;
		if (req->cmd_type != REQ_TYPE_FS) {
			printk("skip non-fs request\n");
			blk_start_request(req);
			__blk_end_request_all(req, -EIO);
			continue;
		}

		blk_start_request(req);
		__rq_for_each_bio(bio,req)
			vmem_disk_xfer_bio(dev, bio);
		__blk_end_request_all(req, 0);
	}	
}

static void setup_device(struct vmem_disk_dev *dev, int which)
{
	memset(dev, 0, sizeof(struct vmem_disk_dev));

	dev->size = N_SECTORS*HWSECTOR_SIZE;
	dev->data = vmalloc(dev->size);
	if (!dev->data) {
		printk("vmalloc failed\n");
		return;
	}
	spin_lock_init(&dev->lock);

	switch (request_mode) {
	case VMEMD_NOQUEUE:
		dev->queue = blk_alloc_queue(GFP_KERNEL);
		if (!dev->queue)
			goto out_vfree;

		blk_queue_make_request(dev->queue, vmem_disk_make_request);
		break;

	default:
		printk("Bad request mode %d, using simple queue.\n", request_mode);

	case VMEMD_QUEUE:
		dev->queue = blk_init_queue(vmem_disk_request, &dev->lock);
		if (!dev->queue)
			goto out_vfree;
		break;
	}

	blk_queue_logical_block_size(dev->queue, HWSECTOR_SIZE);
	dev->queue->queuedata = dev;

	dev->gd = alloc_disk(VMEM_DISK_MINORS);
	if (!dev->gd) {
		printk("alloc_disk failed\n");
		goto out_vfree;
	}

	dev->gd->major = vmem_disk_major;
	dev->gd->first_minor = which * VMEM_DISK_MINORS;
	dev->gd->fops = &vmem_disk_ops;
	dev->gd->queue = dev->queue;
	dev->gd->private_data = dev;
	sprintf(dev->gd->disk_name, "%s%d", DEV_NAME, which);
	set_capacity(dev->gd, N_SECTORS*(HWSECTOR_SIZE/KERNEL_SECTOR_SIZE));
	add_disk(dev->gd);

	return;

out_vfree:
	if (dev->data)
		vfree(dev->data);
}

static int __init vmem_disk_init(void)
{
	int i, ret;

	vmem_disk_major = register_blkdev(vmem_disk_major, DEV_NAME);
	if (vmem_disk_major <= 0) {
		printk("vmem_disk: unable to get major number\n");
		return -EBUSY;
	}

	devices = kzalloc(N_DEVICES * sizeof(struct vmem_disk_dev), GFP_KERNEL);
	if (!devices) {
		ret = -ENOMEM;
		goto out_unregister;
	}

	for (i = 0; i < N_DEVICES; i++)
		setup_device(devices + i, i);

	return 0;

out_unregister:
	unregister_blkdev(vmem_disk_major, DEV_NAME);

	return ret;
}
module_init(vmem_disk_init);

MODULE_LICENSE("GPL v2");
