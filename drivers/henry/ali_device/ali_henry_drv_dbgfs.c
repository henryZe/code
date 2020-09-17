#include <linux/device.h>
#include <linux/debugfs.h>

#include "ali_henry_drv_dbgfs.h"

#define HENRY_DBG_PRINT_BAISC_STATUS		(0)
#define HENRY_DBG_PRINT_TEST				(1)

static int choice = HENRY_DBG_PRINT_BAISC_STATUS;

static int henry_dbg_test(struct seq_file *f,
	struct henry_session *s)
{
	seq_puts(f, "choice: [0]basic, [1]test\n");
	seq_puts(f, "test seq_printf\n");

	return 0;
}

static int henry_show_basic(struct seq_file *f,
	struct henry_session *s)
{
	seq_puts(f, "choice: [0]basic, [1]test\n");

	seq_printf(f, "%12s: %d\n", "session id", s->id);

	return 0;
}

static int henry_show_status(struct seq_file *f, void *p)
{
	struct henry_session *s = f->private;

	if (!s)
		return -ENODEV;

	switch (choice) {
	case HENRY_DBG_PRINT_BAISC_STATUS:
		henry_show_basic(f, s);
	break;

	case HENRY_DBG_PRINT_TEST:
		henry_dbg_test(f, s);
	break;

	default:
		break;
	}

	return 0;
}

static int henry_debugfs_open(struct inode *i, struct file *f)
{
	return single_open(f, henry_show_status, i->i_private);
}

static const struct file_operations henry_status_ops = {
	.open = henry_debugfs_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
	.owner = THIS_MODULE,
};

int henry_dbgfs_add_session(struct henry_session *sess)
{
	char name[128];
	struct henry_drv *drv;

	if (!sess)
		return -1;
	drv = sess->drv;
	if (!drv || !drv->debugfs_dir)
		return -1;

	sprintf(name, "session@%d", sess->id);
	sess->session_dir = debugfs_create_dir(name, drv->debugfs_dir);
	if (!sess->session_dir || IS_ERR(sess->session_dir)) {
		dev_dbg(drv->dev, "create session dir failed\n");
		return -1;
	}

	sprintf(name, "dbg");
	sess->debugfs = debugfs_create_file(name, S_IFREG | S_IRUGO,
		sess->session_dir, (void *)sess, &henry_status_ops);
	if (!sess->debugfs || IS_ERR(sess->debugfs))
		dev_dbg(drv->dev, "debugfs create file failed\n");

	sprintf(name, "choice");
	sess->choice = debugfs_create_u32(name, S_IFREG | S_IRUGO | S_IWUGO,
		sess->session_dir, &choice);
	if (!sess->choice || IS_ERR(sess->choice))
		dev_dbg(drv->dev, "debugfs create choice failed\n");

	return 0;
}

int henry_dbgfs_del_session(struct henry_session *sess)
{
	if (!sess)
		return -1;

	debugfs_remove(sess->debugfs);
	debugfs_remove(sess->choice);

	debugfs_remove(sess->session_dir);

	return 0;
}

void henry_dbgfs_create(struct henry_drv *drv)
{
	drv->debugfs_dir = debugfs_create_dir(HENRY_DBG, NULL);

	if (!drv->debugfs_dir)
		dev_err(drv->dev, "debugfs create dentry failed\n");
}

void henry_dbgfs_remove(struct henry_drv *drv)
{
	if (drv && drv->debugfs_dir)
		debugfs_remove_recursive(drv->debugfs_dir);
}
