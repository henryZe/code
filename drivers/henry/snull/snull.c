#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

#include <linux/sched.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/errno.h>  /* error codes */
#include <linux/types.h>  /* size_t */
#include <linux/interrupt.h> /* mark_bh */

#include <linux/in.h>
#include <linux/netdevice.h>   /* struct device, and other headers */
#include <linux/etherdevice.h> /* eth_type_trans */
#include <linux/ip.h>          /* struct iphdr */
#include <linux/tcp.h>         /* struct tcphdr */
#include <linux/skbuff.h>


struct net_device *snull_devs[2];

/* Finally, the module stuff */
void snull_cleanup(void)
{
	int i;
    
	for (i = 0; i < 2;  i++) {
		if (snull_devs[i]) {
			unregister_netdev(snull_devs[i]);
			snull_teardown_pool(snull_devs[i]);
			free_netdev(snull_devs[i]);
		}
	}
	return;
}

int snull_init_module(void)
{
	int result, i, ret = -ENOMEM;

	snull_interrupt = use_napi ? snull_napi_interrupt : snull_regular_interrupt;

	/* Allocate the devices */
	snull_devs[0] = alloc_netdev(sizeof(struct snull_priv), "sn%d",
			snull_init);
	snull_devs[1] = alloc_netdev(sizeof(struct snull_priv), "sn%d",
			snull_init);
	if (snull_devs[0] == NULL || snull_devs[1] == NULL)
		goto out;

	ret = -ENODEV;
	for (i = 0; i < 2; i++) {
		if (result = register_netdev(snull_devs[i]))
			pr_info("snull: error %i registering device \"%s\"\n",
					result, snull_devs[i]->name);
		else
			ret = 0;
	}

out:
	if (ret) 
		snull_cleanup();
	return ret;
}

module_init(snull_init_module);
module_exit(snull_cleanup);
