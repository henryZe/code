#include <linux/module.h>
#include <linux/netlink.h>
#include <net/sock.h>

#define NETLINK_TEST 17

static struct sock *netlinkfd = NULL;

void netlink_send_message(unsigned int pid)
{
	int size, ret;
	const char *message = "Hello from kernel";
	struct sk_buff *skb = NULL;
	struct nlmsghdr *nlh = NULL;

	size = NLMSG_SPACE(strlen(message));
	skb = alloc_skb(size, GFP_ATOMIC);

	/* init netlink header */
	nlh = nlmsg_put(skb, 0, 0, 0,
			NLMSG_SPACE(strlen(message)) - sizeof(struct nlmsghdr), 0);
	memcpy(NLMSG_DATA(nlh), message, strlen(message));
	nlh->nlmsg_len = size;
	nlh->nlmsg_pid = 0;
	nlh->nlmsg_flags = 0;

	NETLINK_CB(skb).portid = 0;
	NETLINK_CB(skb).dst_group = 0;

	ret = netlink_unicast(netlinkfd, skb, pid, MSG_DONTWAIT);
	if (ret != nlh->nlmsg_len)
		printk("netlink_unicast failed, ret %d\n", ret);
	else
		printk("kernel uni_send message\n");

	ret = netlink_broadcast(netlinkfd, skb, 0, 0, GFP_KERNEL);
	printk("kernel brd_send message\n");
}

void netlink_receive_message(struct sk_buff *skb)
{
	struct nlmsghdr *nlh = NULL;
	u8 *payload = NULL;

	/* process netlink message pointed by skb->data */
	/* netlink_rcv_skb */
	nlh = nlmsg_hdr(skb);
	payload = NLMSG_DATA(nlh);

	printk("Receive message from user pid %d: %s\n",
			nlh->nlmsg_pid, payload);

	netlink_send_message(nlh->nlmsg_pid);
}

int __init netlink_kernel_init(void)
{
	struct netlink_kernel_cfg config;

	memset(&config, 0, sizeof(config));
	config.input = netlink_receive_message;

	netlinkfd = netlink_kernel_create(&init_net,
			NETLINK_TEST, &config);
	if (!netlinkfd)
		printk("netlink_kernel_create failed\n");

	printk("netlink_kernel init\n");

	return 0;
}

void __exit netlink_kernel_exit(void)
{
	netlink_kernel_release(netlinkfd);
	printk("netlink_kernel exit\n");
}

module_init(netlink_kernel_init);
module_exit(netlink_kernel_exit);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("henry.zeng");
