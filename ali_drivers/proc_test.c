#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include "internal.h"

#define BUFF_SIZE 16

static struct proc_dir_entry *test_dir;
static struct proc_dir_entry *test_entry;
static char content[BUFF_SIZE];

static int show_content(struct seq_file *seq, void *p)
{
	char *buff = seq->private;
	seq_printf(seq, "%s", buff);

	return 0;
}

int test_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, show_content, PDE_DATA(inode));
}

ssize_t test_proc_write(struct file *file, const char __user *buf, size_t count, loff_t *off)
{
	size_t size = count;
	struct seq_file *seq = file->private_data;
	char *buff = seq->private;

	if (size > (BUFF_SIZE - 1))
		size = BUFF_SIZE - 1;

	copy_from_user(buff, buf, size);
	buff[size] = 0;

	return size;
}

static const struct file_operations proc_fops = {
	.owner = THIS_MODULE,
	.open = test_proc_open,
	.read = seq_read,
	.write = test_proc_write,
	.llseek = seq_lseek,
	.release = single_release,
};

static __init int test_proc_init(void)
{
	test_dir = proc_mkdir("test_dir", NULL);
	if (!test_dir)
		return -ENOMEM;

	test_entry = proc_create_data("test_rw", 0666, test_dir, &proc_fops, &content);
	if (!test_entry)
		return -ENOMEM;

	return 0;
}
module_init(test_proc_init);

static __exit void test_proc_exit(void)
{
	remove_proc_entry("test_rw", test_dir);
	remove_proc_entry("test_dir", NULL);
}
module_exit(test_proc_exit);

MODULE_AUTHOR("henry.zeng");
MODULE_DESCRIPTION("proc example");
MODULE_LICENSE("GPL v2");
