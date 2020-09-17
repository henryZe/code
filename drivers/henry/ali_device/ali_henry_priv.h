#ifndef _ALI_HENRY_PRIV_H
#define _ALI_HENRY_PRIV_H

#include <linux/cdev.h>
#include <linux/idr.h>

#define HENRY_CLASS "henry_class"
#define HENRY_DEV "henry"
#define HENRY_DBG "henry_debug"

#define VIRTUAL_DEV_NUM 8

struct henry_drv {
	dev_t dev_num;
	struct cdev cdev;
	struct class *dev_class;
	struct device *dev;
	struct mutex mutex;
	int num_exist;
	struct ida sess_ida;

	int debug_mode;
	struct dentry *debugfs_dir;
};

struct page_msg {
	struct list_head node;
	struct page *page;
	unsigned int offset;
	unsigned int len;
};

struct buffer_msg {
	struct mutex queue_lock;
	struct list_head page_head;
};

struct henry_session {
	struct henry_drv *drv;
	unsigned int id;
	struct buffer_msg buffer;
	wait_queue_head_t poll_wq;

	struct dentry *session_dir;
	struct dentry *debugfs;
	struct dentry *choice;
};

#endif
