#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/platform_device.h>
#include <linux/irq.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/interrupt.h>

#include <linux/netdevice.h>
#include <linux/etherdevice.h>

#include <linux/workqueue.h>


struct net_device *henry_net;
struct net_device_stats net_stats =
{
	.rx_packets = 0,
	.tx_packets = 0,
	
	.rx_bytes = 0,
	.tx_bytes = 0,
};


static int gec_net_init(struct net_device *dev)
{
	printk(KERN_INFO "gec_net_init\n");
	return 0;
}


static void gec_net_uninit(struct net_device *dev)
{
	printk(KERN_INFO "gec_net_uninit\n");
}


static int gec_net_open(struct net_device *dev)
{
	printk(KERN_INFO "gec_net_open\n");
	//告诉kernel驱动空间有缓冲区skb可用,开始发送数据包到driver
	netif_start_queue(dev);
	
	return 0;
}


static int gec_net_stop(struct net_device *dev)
{
	printk(KERN_INFO "gec_net_stop\n");
	//函数停止接受数据之后，driver把缓冲区skb的数据发送到网络device中，然后调用该函数通知kernel继续发送数据包到driver
	netif_stop_queue(dev);
	
	return 0;
}


//socket buffer kernel自动生成传递给driver
static netdev_tx_t gec_net_transmit(struct sk_buff *skb, struct net_device *dev)
{
	int len;
	printk(KERN_INFO "gec_net_transfer\n");
	
	if(!skb)
	{
		goto err1;
	}

	len = skb->len > ETH_ZLEN? skb->len:ETH_ZLEN;
	//固件发送函数
	//hardware_trans_data(skb->data, len, dev);
	
	dev->stats.tx_packets += 1,
	dev->stats.tx_bytes += len,
	
	dev_kfree_skb(skb);

	return NETDEV_TX_OK;


err1:
	printk(KERN_ERR "socket buffer is NULL!\n");
	return NETDEV_TX_BUSY;
}


struct work_struct receive_pack;


static int gec_net_receive_after(struct work_struct *work)
{
	int len = henry_net->mem_end - henry_net->mem_start;
	char *buffer = henry_net->mem_start;


	//driver创建socket_buffer
	struct sk_buff *skb;
	skb = dev_alloc_skb(len+2);
	if(!skb)
	{
		goto err1;
	}
	
	//14bytes,4bytes 对齐
	skb_reserve(skb, 2);
	//接收数据
	memcpy(skb_put(skb, len), buffer, len);
	
	henry_net->stats.rx_packets += 1,
	henry_net->stats.rx_bytes += len,
	skb->dev = henry_net;
	//ether协议类型,对skb进行包装以通过内核的各个协议层
	skb->protocol = eth_type_trans(skb, henry_net);
	skb->ip_summed = CHECKSUM_UNNECESSARY;

	
	//内核函数,将skb发送给内核(协议层)
	netif_rx(skb);

	
	return 0;

err1:
	printk(KERN_ERR "socket buffer is NULL!\n");
	return -1;
}


static irqreturn_t gec_net_receive_front(int irq, void *dev_id)
{
	printk("interrupt receive come!\n");
	
	schedule_work(&receive_pack);
	
	return IRQ_HANDLED;	
}


struct net_device_ops ndev_ops =
{
	.ndo_init = gec_net_init,
	.ndo_uninit = gec_net_uninit,
	.ndo_open = gec_net_open,
	.ndo_stop = gec_net_stop,
	.ndo_start_xmit = gec_net_transmit,
};


static int gec_header(struct sk_buff *skb, struct net_device *dev, unsigned short type, const void *daddr, const void *saddr, unsigned len)
{
	printk(KERN_INFO "gec_header\n");
	return 0;
}


static const struct header_ops henry_header_ops =
{
	.create = gec_header,
};


typedef struct board_info {

	void __iomem	*io_addr;	/* Register I/O base address */
	void __iomem	*io_data;	/* Data I/O address */
	u16		 irq;		/* IRQ */

	u16		tx_pkt_cnt;
	u16		queue_pkt_len;
	u16		queue_start_addr;
	u16		queue_ip_summed;
	u16		dbug_cnt;
	u8		io_mode;		/* 0:word, 2:byte */
	u8		phy_addr;
	u8		imr_all;

	unsigned int	flags;
	unsigned int	in_suspend :1;
	unsigned int	wake_supported :1;
	int		debug_level;


	void (*inblk)(void __iomem *port, void *data, int length);
	void (*outblk)(void __iomem *port, void *data, int length);
	void (*dumpblk)(void __iomem *port, int length);

	struct device	*dev;	     /* parent device */

	struct resource	*addr_res;   /* resources found */
	struct resource *data_res;
	struct resource	*addr_req;   /* resources requested */
	struct resource *data_req;
	
	struct resource *irq_res;

	int		 irq_wake;

	struct mutex	 addr_lock;	/* phy and eeprom access lock */

	struct delayed_work phy_poll;
	struct net_device  *ndev;

	spinlock_t	lock;

	u32		msg_enable;
	u32		wake_state;

	int		rx_csum;
	int		can_csum;
	int		ip_summed;
} board_info_t;


struct board_info *db;


static int dm9000_probe(struct platform_device *pdev)
{
	int i;	

	
	//1.分配空间
	henry_net = alloc_etherdev(sizeof(struct net_device));
	
	//2.填充net_device结构体
	//以太网设备初始化,14字节以太网头部,4个字节对齐,so reserve 2 Bytes
	ether_setup(henry_net);
	//sprintf(henry_net->name, "gec_net%d", 0);
	//设置初始状态值
	henry_net->stats = net_stats;
	henry_net->netdev_ops = &ndev_ops;
	//以太网报文头部 操作函数可以自定义
	//henry_net->header_ops = &henry_header_ops;

//MAC address	
#ifndef MAC_AUTO
	for(i=0; i<6; i++)
	{
		henry_net->dev_addr[i] = 0xa;
	}
#else
	//随机源地址
	random_ether_addr(henry_net->dev_addr);
#endif
	
	//可以传递私有数据指针
	//henry_net->ml_priv = (void *)&data_pointer;


	//硬件初始化
	//1.get_resource (2.request mem) 3.ioremap
	db->addr_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	db->data_res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	db->irq_res  = platform_get_resource(pdev, IORESOURCE_IRQ, 0);

	INIT_WORK(&receive_pack, gec_net_receive_after);

	db->addr_req = request_mem_region(db->addr_res->start, resource_size(db->addr_res), db->addr_res->name);
	db->data_req = request_mem_region(db->data_res->start, resource_size(db->data_res), db->data_res->name);
	db->addr_req = request_irq(db->irq_res->start, gec_net_receive_front, IRQF_PROBE_SHARED|IRQF_TRIGGER_HIGH, "receive package", NULL);

	
	//3.注册结构体
	register_netdev(henry_net);

	return 0;
}	


static int dm9000_remove(struct platform_device *pdev)
{
	unregister_netdev(henry_net);
	free_netdev(henry_net);

	iounmap(db->io_addr);
	iounmap(db->io_data);

	release_mem_region(db->addr_req->start, resource_size(db->addr_req));
	release_mem_region(db->data_req->start, resource_size(db->data_req));
	
	return 0;
}


static struct platform_driver dm9000_driver = 
{
	.driver	= 
	{
		.name    = "dm9000",
		.owner	 = THIS_MODULE,
	},
	.probe   = dm9000_probe,
	.remove  = dm9000_remove,
};


static int __init net_drv_init(void)
{
	return platform_driver_register(&dm9000_driver);
}


static void __exit net_drv_exit(void)
{
	platform_driver_unregister(&dm9000_driver);
}


module_init(net_drv_init);
module_exit(net_drv_exit);

MODULE_AUTHOR("henry_Z");
MODULE_DESCRIPTION("net driver");
MODULE_VERSION("v0.1");
MODULE_LICENSE("GPL");
