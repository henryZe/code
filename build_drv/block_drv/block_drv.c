#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/genhd.h>
#include <linux/spinlock.h>
#include <linux/blkdev.h>


#define MAX_SIZE 1024*1024
char nand_flash[MAX_SIZE];


struct gendisk *gec_disk;
int blk_major;
spinlock_t gec_lock = SPIN_LOCK_UNLOCKED;


static int gec_blk_open(struct block_device *bdev, fmode_t mode)
{
	printk(KERN_ERR "gec_blk_open\n");
	return 0;
}

static int gec_blk_release(struct gendisk *gen_disk, fmode_t mode)
{
	printk(KERN_ERR "gec_blk_release\n");
	return 0;
}


struct block_device_operations gec_dops =
{	
	.owner = THIS_MODULE,
	.open = gec_blk_open,
	.release = gec_blk_release,
};


void gec_blk_transfer(int sector, int sectors, char *buffer, int direct)
{
	//读:0; 写:1
	if(direct)
	{
		memcpy(nand_flash+sector*512, buffer, sectors*512);
	}

	else
	{
		memcpy(buffer, nand_flash+sector*512, sectors*512);
	}
}


void gec_request_fn(struct request_queue *q)
{
	struct request *req;
	
	//blk_fetch_request从当前的q请求队列中提出下一个出队的request
	while((req = blk_fetch_request(q)) != NULL)
	{
		//判断当前request是否为一个文件系统操作,是则返回真(blk_fs_request)
		if(!blk_fs_request(req))
		{
			//由于不是来自文件系统的操作请求，则停止该请求处理
			__blk_end_request_all(req, -EIO);
			continue;
		}
		
		//blk_rq_pos：获得当前操作的扇区号;
		//blk_rq_sectors:获得当前操作的扇区数量;
		//req->buffer：本次操作的数据缓冲区地址；
		//rq_data_dir：获得本次操作的方向；读或者写
		gec_blk_transfer(blk_rq_pos(req), blk_rq_sectors(req), req->buffer, rq_data_dir(req));
		//返回0表示成功 结束request处理
		__blk_end_request_all(req, 0);
	}
}


static int __init gec_disk_init(void)
{
	//注册设备号
	blk_major = register_blkdev(0, "gec_blk");
	if(blk_major<0)
	{
		goto fail;
	}
	
	
	//注册设备
	//request room,one device
	gec_disk = alloc_disk(1);
	

	//fill in
	gec_disk->major = blk_major;
	gec_disk->first_minor = 0;
	gec_disk->fops = &gec_dops;
	//初始化request队列
	//使用内核的默认算法进行合并请求(bio->request)
	gec_disk->queue = blk_init_queue(gec_request_fn, &gec_lock);
	//配置了当前硬盘的每个扇区为512字节大小
	blk_queue_logical_block_size(gec_disk->queue, 512);
	//设置当前硬盘的容量为2048个扇区,折合1M内存
	set_capacity(gec_disk, 2048);
	//命名
	sprintf(gec_disk->disk_name, "gecblock%d", 1);


	//对硬件进行格式化
	memset(nand_flash, 0, sizeof(nand_flash));


	//register
	add_disk(gec_disk);


	return 0;

fail:
	printk(KERN_ERR "register block device fail\n");
	return -ENODEV;	
}


static void __exit gec_disk_exit(void)
{	
	unregister_blkdev(blk_major, "gec_blk");
	blk_cleanup_queue(gec_disk->queue);
	del_gendisk(gec_disk);
}


module_init(gec_disk_init);
module_exit(gec_disk_exit);

MODULE_LICENSE("GPL");
