#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/fb.h>
#include <linux/ioport.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <linux/dma-mapping.h>
#include "lcd_dev.h"


#define AT_SAMSUNG_ANDROID


struct fb_info  *gec_fb;
unsigned char  *vir_mem;
unsigned long phy_mem;
struct resource *lcd_res[28], *lcd_req[28];
unsigned long  *lcd_rmp[28];


static int gec_fb_mmap(struct fb_info *info, struct vm_area_struct *vma)
{	
	int ret;
	
	//virtual memory vma,内核自动生成,将物理页地址,映射到vma,直接用户空间调用
	ret = remap_pfn_range(
				vma,
				vma->vm_start,
				phy_mem>>PAGE_SHIFT,
				vma->vm_end - vma->vm_start,
				vma->vm_page_prot);
	
	if(ret)
	{
		goto remap_pfn_range_err;
	}
	
	return 0;
	
remap_pfn_range_err:
	printk(KERN_ERR "remap pfn range error!\n");
	return -EFAULT;
}


struct fb_ops gec_fbops = 
{	
	//virtual memory vma,与应用程序的mmap接口函数
	.fb_mmap = gec_fb_mmap,
};


static int lcd_init(struct platform_device *pdev)
{
	int i;
	
	for(i=0; i<28; i++)
	{
		lcd_res[i]= platform_get_resource(pdev, IORESOURCE_MEM, i);

		if(!lcd_res[i])
		{
			goto platform_get_resource_err;
		}

#ifndef  AT_SAMSUNG_ANDROID
		lcd_req[i] = request_mem_region(lcd_res[i]->start, resource_size(lcd_res[i]), lcd_res[i]->name);
		if(!lcd_req[i])
		{
			goto request_mem_region_err;
		}

#else

		lcd_req[i] = lcd_res[i];

#endif
		lcd_rmp[i] = ioremap(lcd_req[i]->start, resource_size(lcd_req[i]));
		if(!lcd_rmp[i])
		{
			goto ioremap_err;
		}
	}
		
	// 配置引脚用于LCD功能
	for(i=0; i<4; i++)
	{
		*lcd_rmp[i] = 0x22222222;
	}

	// 配置LCD CLK 使能
	*lcd_rmp[5]  = *lcd_rmp[5] | 0x1;


	// 配置PIMD CLK 时钟源SCLK
	*lcd_rmp[6]  = *lcd_rmp[6] | ( 0x6 << 20);  
	// 配置PIMD CLK分频比
	*lcd_rmp[7]  = *lcd_rmp[7] | ( 0x3 << 20); 

	
	// 配置显示方式为PIMD
	// 10: RGB=FIMD I80=FIMD ITU=FIMD
	*lcd_rmp[8] = 2<<0;

	// bit[26~28]:使用RGB接口
	// bit[18]:RGB 并行
	// bit[2]:选择时钟源为HCLK_DSYS=166MHz
	*lcd_rmp[9] =  *lcd_rmp[9] & (~( (3<<26)|(1<<18)|(1<<16)|(1<<5)|(1<<2) ));



	// bit[4]:选择需要分频
	// bit[6~13]:分频系数为15，即VCLK = 166M/(14+1) = 11M
	*lcd_rmp[9] =  *lcd_rmp[9] | ((10<<6) | (1<<4));

	// bit[1]:使能lcd控制器
	// bit[0]:当前帧结束后使能lcd控制器
	*lcd_rmp[9] =	*lcd_rmp[9] | ( (1<<0)|(1<<1) );


	// H43-HSD043I9W1.pdf(p13) 时序图：VSYNC和HSYNC都是低脉冲
	// s5pv210芯片手册(p1207) 时序图：VSYNC和HSYNC都是高脉冲有效，所以需要反转
	*lcd_rmp[10]  = *lcd_rmp[10] | ((1<<5) | (1<<6));

	// 设置时序
	*lcd_rmp[12] = VBPD<<16 | VFPD<<8 | VSPW<<0;
	*lcd_rmp[13] = HBPD<<16 | HFPD<<8 | HSPW<<0;
	// 设置长宽
	*lcd_rmp[14] = (LINEVAL << 11) | (HOZVAL << 0);

	// 设置windows0
	// bit[0]:使能
	// bit[2~5]:16bpp
	*lcd_rmp[15] = *lcd_rmp[15] | (1<<0);
	*lcd_rmp[15] = *lcd_rmp[15] & (~(0xf << 2));
	*lcd_rmp[15] = *lcd_rmp[15] | ((0xB<<2) | (1<<15));


	// 使能channel 0传输数据
	*lcd_rmp[17] = 0x1 << 0 ;

	// 设置windows0的上下左右
	*lcd_rmp[18] = (LeftTopX<<11) | (LeftTopY << 0);
	*lcd_rmp[19] = (RightBotX<<11) | (RightBotY << 0);
	*lcd_rmp[20] = (LINEVAL + 1) * (HOZVAL + 1);


	// 设置fb的地址
	*lcd_rmp[21] = phy_mem;
	*lcd_rmp[22] =  *lcd_rmp[21] + ((((HOZVAL + 1)*4 + 0) * (LINEVAL + 1)) & (0xffffff));
	*lcd_rmp[23] = 0x0 << 13 |  800 *4<< 0 ;

	
  	return 0;
	
platform_get_resource_err:
	printk(KERN_ERR "platform get resource Failed!\n");
	return -EFAULT;		


#ifndef  AT_SAMSUNG_ANDROID
request_mem_region_err:
	printk(KERN_ERR "request mem region Failed!\n");
	for(i=i-1; i>=0; i--)
	{
		release_mem_region(lcd_res[i]->start, resource_size(lcd_res[i]));
	}
	return -EFAULT;	
#endif


ioremap_err:
	printk(KERN_ERR "ioremap Failed!\n");
	for(i=i-1; i>=0; i--)
	{
		iounmap(lcd_rmp[i]);
	}
	return -EFAULT;		
}


static int lcd_exit(void)
{
	int i;
	for(i=0; i<28; i++)
	{
		iounmap(lcd_rmp[i]);

#ifndef  AT_SAMSUNG_ANDROID
		release_mem_region(lcd_res[i]->start, resource_size(lcd_res[i]));
#endif

	}
	return 0;
}


static int gec_lcd_probe(struct platform_device *pdev)
{
	int ret;
	
	gec_fb = framebuffer_alloc(sizeof(struct fb_info), &pdev->dev);
	if(!gec_fb)
	{
		goto framebuffer_alloc_err;
	}


	gec_fb->var.xres = 800;
	gec_fb->var.yres = 480;
	gec_fb->var.xoffset = 0;
	gec_fb->var.yoffset = 0;
	gec_fb->var.bits_per_pixel = 32;
	gec_fb->var.width = 800;
	gec_fb->var.height = 480;
	gec_fb->var.pixclock = (FB_FREQ * (HBPD + HFPD + HSPW + COL) + (VBPD + VFPD + VSPW + ROW));	
	gec_fb->var.left_margin = HBPD;
	gec_fb->var.right_margin = HFPD;
	gec_fb->var.upper_margin = VBPD;
	gec_fb->var.lower_margin = VFPD;
	gec_fb->var.hsync_len = HSPW;
	gec_fb->var.vsync_len = VSPW;

	
	vir_mem = kmalloc(COL*ROW*4, GFP_KERNEL);
	phy_mem = __pa(vir_mem);
	
	gec_fb->fix.smem_start = phy_mem;
	gec_fb->fix.smem_len = COL*ROW*4;

	gec_fb->fbops = &gec_fbops;
	
	gec_fb->screen_base = vir_mem;
	gec_fb->screen_size = COL*ROW*4;

	gec_fb->par = NULL;

	
	lcd_init(pdev);


	ret = register_framebuffer(gec_fb);
	if(ret)
	{
		goto register_framebuffer_err;
	}


	return 0;

framebuffer_alloc_err:
	printk(KERN_ERR "framebuffer alloc failed!\n");
	return -EFAULT;

register_framebuffer_err:
	printk(KERN_ERR "register framebuffer failed!\n");
	return -EFAULT;
}


static int gec_lcd_remove(struct platform_device *pdev)
{
	kfree(vir_mem);
	lcd_exit();
	unregister_framebuffer(gec_fb);
	
	return 0;
}


struct platform_driver  gec_lcd_drv =
{
	.probe  = gec_lcd_probe,
	.remove = gec_lcd_remove,
	.driver = 
	{
		.name = "gec_lcd",
	},
};


static int __init lcd_drv_init(void)
{
	int ret;
	ret = platform_driver_register(&gec_lcd_drv);
	if(ret)
	{
		goto platform_driver_register_err;
	}

	return 0;
	
platform_driver_register_err:
	printk(KERN_ERR "platform driver register failed!\n");
	return -EFAULT;		
}


static void __exit lcd_drv_exit(void)
{
	platform_driver_unregister(&gec_lcd_drv);
}


module_init(lcd_drv_init);
module_exit(lcd_drv_exit);

MODULE_LICENSE("GPL");
