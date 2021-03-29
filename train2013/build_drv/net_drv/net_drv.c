#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/netdevice.h>
#include <linux/etherdevice.h>


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


static int gec_net_receive(struct net_device *dev, int len, unsigned char *buffer)
{
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
	
	dev->stats.rx_packets += 1,
	dev->stats.rx_bytes += len,
	skb->dev = dev;
	//ether协议类型,对skb进行包装以通过内核的各个协议层
	skb->protocol = eth_type_trans(skb, dev);
	skb->ip_summed = CHECKSUM_UNNECESSARY;

	
	//内核函数,将skb发送给内核(协议层)
	netif_rx(skb);

	
	return 0;

err1:
	printk(KERN_ERR "socket buffer is NULL!\n");
	return -1;
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


static int __init net_drv_init(void)
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

	
	//3.注册结构体
	register_netdev(henry_net);

	return 0;
}	


static void __exit net_drv_exit(void)
{
	unregister_netdev(henry_net);
}


module_init(net_drv_init);
module_exit(net_drv_exit);

MODULE_AUTHOR("henry_Z");
MODULE_DESCRIPTION("net driver");
MODULE_VERSION("v0.1");
MODULE_LICENSE("GPL");
