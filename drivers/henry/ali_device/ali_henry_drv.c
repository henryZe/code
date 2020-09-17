#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/splice.h>
#include <linux/highmem.h>
#include <linux/sched.h>
#include <linux/mm.h>

#include <see_bus.h>
#include "ali_henry_drv_dbgfs.h"
#include "ali_henry_drv_sys.h"
#include "ali_henry_priv.h"

#ifdef CONFIG_MEM_TEST
#include "ali_henry_molloc_test.h"
#endif

static int henry_open
(
	struct inode *inode,
	struct file  *file
)
{
	struct henry_drv *drv =
		container_of(file->f_dentry->d_inode->i_cdev,
		struct henry_drv, cdev);
	struct henry_session *session;
	int ret;

#ifdef CONFIG_MEM_TEST
	mem_alloc_page();
	mem_kmalloc();
	mem_vmalloc();
#endif

	mutex_lock(&drv->mutex);

	if (drv->num_exist >= VIRTUAL_DEV_NUM) {
		ret = -EBUSY;
		goto open_fail;
	}

	session = devm_kzalloc(drv->dev,
		sizeof(struct henry_session), GFP_KERNEL);
	if (!session) {
		ret = -ENOMEM;
		goto open_fail;
	}
	session->drv = drv;
	session->id = ida_simple_get(&drv->sess_ida, 0, 0, GFP_KERNEL);
	file->private_data = (void *)session;

	drv->num_exist++;

	init_waitqueue_head(&session->poll_wq);
	mutex_init(&session->buffer.queue_lock);
	INIT_LIST_HEAD(&session->buffer.page_head);

	henry_dbgfs_add_session(session);

	mutex_unlock(&drv->mutex);

	dev_info(drv->dev, "henry_drv_open\n");

	return 0;

open_fail:
	mutex_unlock(&drv->mutex);

	return ret;
}

static int henry_close
(
	struct inode *inode,
	struct file  *file
)
{
	struct henry_session *session = file->private_data;
	struct henry_drv *drv = session->drv;

	/*Do not release resource in debug*/
	if (drv->debug_mode)
		return 0;

	mutex_lock(&drv->mutex);

	ida_simple_remove(&drv->sess_ida, session->id);
	drv->num_exist--;
	henry_dbgfs_del_session(session);
	devm_kfree(drv->dev, session);

	mutex_unlock(&drv->mutex);

	dev_info(drv->dev, "henry_drv_close\n");

	return 0;
}

static ssize_t henry_read(struct file *file,
	char __user *buf, size_t size, loff_t *f_pos)
{
	struct henry_drv *drv =
		container_of(file->f_dentry->d_inode->i_cdev,
		struct henry_drv, cdev);

	dev_info(drv->dev, "henry_drv_read\n");
	return 0;
}

static ssize_t henry_write(struct file *file,
	const char __user *buf, size_t size, loff_t *offset)
{
	struct henry_drv *drv =
		container_of(file->f_dentry->d_inode->i_cdev,
		struct henry_drv, cdev);

	dev_info(drv->dev, "henry_drv_write\n");
	return 0;
}

static int henry_splice_wr_avail(struct buffer_msg *buffer)
{
	int ret;

	mutex_lock(&buffer->queue_lock);
	ret = list_empty(&buffer->page_head);
	mutex_unlock(&buffer->queue_lock);

	return ret;
}

static int henry_splice_rd_avail(struct buffer_msg *buffer)
{
	int ret;

	mutex_lock(&buffer->queue_lock);
	ret = !list_empty(&buffer->page_head);
	mutex_unlock(&buffer->queue_lock);

	return ret;
}

unsigned int henry_poll(struct file *file, struct poll_table_struct *wait)
{
	int ret, mask = 0;
	struct henry_session *session = file->private_data;
	wait_queue_head_t *wq = &session->poll_wq;

	printk("poll_wait enter\n");
	poll_wait(file, wq, wait);

	ret = henry_splice_wr_avail(&session->buffer);
	if (ret) {
		mask |= POLLOUT | POLLWRNORM;
		dev_dbg(session->drv->dev, "%s w_mask POLLOUT\n", __func__);
	}

	ret = henry_splice_rd_avail(&session->buffer);
	if (ret) {
		mask |= POLLIN | POLLRDNORM;
		dev_dbg(session->drv->dev, "%s r_mask POLLIN\n", __func__);
	}

	printk("poll_wait mask %x\n", mask);

	return mask;
}

/* actor: call it one-time per page */
static int pipe_to_henry(struct pipe_inode_info *pipe,
	struct pipe_buffer *buf, struct splice_desc *sd)
{
	unsigned int offset, this_len;
	struct file *filp = sd->u.file;
	struct henry_session *session;
	struct page_msg *node;

	if (unlikely(!filp))
		return -EBADF;

	session = (struct henry_session *)filp->private_data;
	if (unlikely(!session))
		return -EBADF;

	if (unlikely(!buf->page))
		return -EPIPE;

	offset = sd->pos & ~PAGE_MASK;
	this_len = sd->len;
	if (this_len + offset > PAGE_SIZE)
		this_len = PAGE_SIZE - offset;

	printk("%s sd->pos %lld sd->len %d sd->total_len %d this_len %d offset %d\n",
		__func__, sd->pos, sd->len, sd->total_len, this_len, offset);

	node = devm_kzalloc(session->drv->dev,
			sizeof(struct page_msg), GFP_KERNEL);
	if (unlikely(!node))
		return -ENOMEM;

	mutex_lock(&session->buffer.queue_lock);

#if 1
	/* COPY */

	/* increase reference count of page */
	struct page *page = alloc_page(GFP_KERNEL);
	if (unlikely(!page)) {
		mutex_unlock(&session->buffer.queue_lock);
		return -ENOMEM;
	}

	/*  */
	dma_map_page(NULL, buf->page, buf->offset, buf->len, DMA_TO_DEVICE);

	char *src = buf->ops->map(pipe, buf, 1);
	char *dst = kmap_atomic(page);
	/* func: memcpy(dst + offset, src + buf->offset, this_len); */
	kunmap_atomic(dst);
	buf->ops->unmap(pipe, buf, src);

	dma_map_page(NULL, page, offset, this_len, DMA_FROM_DEVICE);
	printk("%02x %02x %02x %02x\n",
			*(dst + offset),
			*(dst + offset + 1),
			*(dst + offset + 2),
			*(dst + offset + 3));
	/*  */

	node->page = page;
	node->len = this_len;
	node->offset = offset;

#else
	/* MOVE */

	/* increase reference count of page */
	get_page(buf->page);

	node->page = buf->page;
	node->len = buf->len;
	node->offset = buf->offset;

#endif

	list_add_tail(&node->node, &session->buffer.page_head);

	mutex_unlock(&session->buffer.queue_lock);

	wake_up_interruptible(&session->poll_wq);

	return node->len;
}

ssize_t henry_splice_write(struct pipe_inode_info *pipe,
				   struct file *filp, loff_t *ppos,
				   size_t count, unsigned int flags)
{
	int ret;

	/* from pipe */
	ret = splice_from_pipe(pipe, filp, ppos, count, flags, pipe_to_henry);
	*ppos += ret;

	return ret;
}

void henry_spd_release(struct splice_pipe_desc *spd, unsigned int page_index)
{
	/* decrease reference count of page */
	put_page(spd->pages[page_index]);
}

static const struct pipe_buf_operations generic_pipe_ops = {
	.can_merge = 0,
	.map = generic_pipe_buf_map,
	.unmap = generic_pipe_buf_unmap,
	.confirm = generic_pipe_buf_confirm,
	.release = generic_pipe_buf_release,
	.steal = generic_pipe_buf_steal,
	.get = generic_pipe_buf_get,
};

ssize_t henry_splice_read(struct file *file, loff_t *ppos,
				  struct pipe_inode_info *pipe, size_t count,
				  unsigned int flags)
{
	int ret, i = 0;
	struct page_msg *node, *node_n;
	struct henry_session *session;
	struct page *pages[PIPE_DEF_BUFFERS];
	struct partial_page partial[PIPE_DEF_BUFFERS];
	struct splice_pipe_desc spd = {
		.pages = pages,
		.partial = partial,
		.nr_pages_max = PIPE_DEF_BUFFERS,
		.flags = flags,
		.ops = &generic_pipe_ops,
		/* call it in the end of splice_to_pipe */
		.spd_release = henry_spd_release,
	};

	session = (struct henry_session *)file->private_data;
	if (unlikely(!session))
		return -EBADF;

	/* alloc spd */
	ret = splice_grow_spd(pipe, &spd);
	if (unlikely(ret))
		return -ENOMEM;

	mutex_lock(&session->buffer.queue_lock);

	list_for_each_entry_safe(node, node_n, &session->buffer.page_head, node) {
		spd.partial[i].len = node->len;
		spd.partial[i].offset = node->offset;
		spd.pages[i] = node->page;

		list_del_init(&node->node);
		devm_kfree(session->drv->dev, node);
		i++;
	}

	spd.nr_pages = i;

	printk("%s nrbufs %d, curbuf %d, buffers %d, ppos %lld, spd.nr_pages %d\n",
		__func__, pipe->nrbufs, pipe->curbuf, pipe->buffers, *ppos, spd.nr_pages);

	/* to pipe file */
	ret = splice_to_pipe(pipe, &spd);
	*ppos += ret;

	mutex_unlock(&session->buffer.queue_lock);

	/* free spd */
	splice_shrink_spd(&spd);

	wake_up_interruptible(&session->poll_wq);

	return ret;
}

static const struct file_operations g_henry_fops = {
	.open = henry_open,
	.release = henry_close,

	.write = henry_write,
	.read = henry_read,

	.poll = henry_poll,

	.splice_write = henry_splice_write,
	.splice_read = henry_splice_read,
};

static int henry_drv_probe(struct see_client *clnt)
{
	int ret = 0;
	struct henry_drv *drv = NULL;

	drv = kzalloc(sizeof(struct henry_drv), GFP_KERNEL);
	if (!drv)
		return -ENOMEM;

	ret = alloc_chrdev_region(&drv->dev_num, 0, 1, HENRY_DEV);
	if (ret < 0)
		return ret;

	cdev_init(&drv->cdev, &g_henry_fops);
	drv->cdev.owner = THIS_MODULE;
	ret = cdev_add(&drv->cdev, drv->dev_num, 1);
	if (ret < 0)
		goto out;

	drv->dev_class = class_create(THIS_MODULE, HENRY_CLASS);
	if (IS_ERR_OR_NULL(drv->dev_class)) {
		ret = PTR_ERR(drv->dev_class);
		goto out;
	}

	drv->dev = device_create(drv->dev_class, NULL, drv->dev_num, drv,
						HENRY_DEV);
	if (IS_ERR_OR_NULL(drv->dev)) {
		ret = PTR_ERR(drv->dev);
		goto out;
	}

	mutex_init(&drv->mutex);
	drv->num_exist = 0;
	drv->debug_mode = 0;
	ida_init(&drv->sess_ida);

	dev_set_drvdata(&clnt->dev, drv);

	henry_sysfs_create(drv);
	henry_dbgfs_create(drv);

	dev_info(&clnt->dev, "HENRY driver probed\n");

out:
	if (unlikely(ret)) {
		if (drv->dev_class) {
			/* device_create */
			device_destroy(drv->dev_class, drv->dev_num);
			/* cdev_add */
			cdev_del(&drv->cdev);
			/* class_create */
			class_destroy(drv->dev_class);
			/* alloc_chrdev_region */
			unregister_chrdev_region(drv->dev_num, 1);
		}
		kfree(drv);
	}

	return ret;
}

int henry_drv_remove(struct see_client *clnt)
{
	struct henry_drv *drv = dev_get_drvdata(&clnt->dev);

	henry_sysfs_remove(drv);
	henry_dbgfs_remove(drv);

	mutex_destroy(&drv->mutex);
	ida_destroy(&drv->sess_ida);
	unregister_chrdev_region(drv->dev_num, 1);
	device_destroy(drv->dev_class, drv->dev_num);
	cdev_del(&drv->cdev);
	class_destroy(drv->dev_class);
	kfree(drv);

	dev_info(&clnt->dev, "HENRY driver removed\n");

	return 0;
}

static const struct of_device_id see_henry_matchtbl[] = {
	{ .compatible = "alitech,henry" },
	{ }
};

static struct see_client_driver henry_drv = {
	.probe	= henry_drv_probe,
	.remove	= henry_drv_remove,
	.driver	= {
		.name = "HENRY",
		.of_match_table	= see_henry_matchtbl,
	},
	.see_min_version = SEE_MIN_VERSION(2, 0, 3, 0),
};

module_see_client_driver(henry_drv);

MODULE_AUTHOR("ALi (Zhuhai) Corporation");
MODULE_DESCRIPTION("HENRY Driver for testing");
MODULE_LICENSE("GPL v2");
MODULE_VERSION("1.1.0");
