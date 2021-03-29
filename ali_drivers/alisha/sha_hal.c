#include "ali_sha.h"
#include "sha_reg.h"

#define DUMP(data,len) \
    do{ \
        int i, l=(len); \
        for(i=0; i<l; i++){ \
            printk("%08X,", ioread32((unsigned long *)data + i)); \
            if((i+1)%16==0) \
                printk("\n"); \
        } \
        if((i)%16==0) \
            printk("\n"); \
        else \
            printk("\n\n"); \
    }while(0)

static void ali_sha_hal_init(struct ali_sha_hw_state *p_sha_dev)
{
	sha_mode_set(p_sha_dev->pdev->io_base, p_sha_dev->sha_work_mode);
	sha_data_source_select(p_sha_dev->pdev->io_base, 0);

	/*NOTE: !!
	   when SHA running at scatter mode, have to make sure that the first and
	   intermediate data are multiples of SHA block-size (64/128 bytes). Otherwise,
	   cannot receive DMA interrupts.
	 */
	sha_set_scatter_mode(p_sha_dev->pdev->io_base, p_sha_dev->scatter_mode);

	sha_set_dma_stage(p_sha_dev->pdev->io_base, p_sha_dev->dma_stage);
	sha_set_int_value(p_sha_dev->pdev->io_base, p_sha_dev->iv);
	sha_set_total_len(p_sha_dev->pdev->io_base, p_sha_dev->total_length);
}

int sha_hal_digest(struct ali_sha_hw_state *p_sha_dev,
		dma_addr_t input, unsigned char *output)
{
	int ret = 0;
	unsigned int digest_sel = 0;
	unsigned int i = 0;

	if ((p_sha_dev->total_length > p_sha_dev->pdev->max_sha_size) ||
	    (p_sha_dev->data_length > p_sha_dev->pdev->max_sha_size))
		return -EFBIG;

	switch (p_sha_dev->sha_work_mode) {
	case SHA_SHA_1:
		digest_sel = 0x4;
		break;
	case SHA_SHA_224:
		digest_sel = 0x6;
		break;
	case SHA_SHA_256:
		digest_sel = 0x7;
		break;
	case SHA_SHA_384:
		digest_sel = 0xb;
		break;
	case SHA_SHA_512:
		digest_sel = 0xf;
		break;
	default:
		printk("sha work mode error\n");
		return -EINVAL;
	}

	mutex_lock(&p_sha_dev->pdev->mutex);

	ali_sha_hal_init(p_sha_dev);

	data_seq_set(p_sha_dev->pdev->io_base, DATA_BIG_ENDIAN);
	/*2. dma control */
	dma_interrupt_enable(p_sha_dev->pdev->io_base, DMA_TRANSFER_END_CHECK_EN);
	dma_dma_mode_select(p_sha_dev->pdev->io_base, PURE_DATA_MODE);
	dma_data_target_select(p_sha_dev->pdev->io_base, DMA_DATA_TARGET_IS_SHA);

	dma_src_addr_set(p_sha_dev->pdev->io_base, input);
	dma_transfer_length_set(p_sha_dev->pdev->io_base,
			p_sha_dev->data_length, PURE_DATA_MODE);
	sha_endian_select(p_sha_dev->pdev->io_base, SHA_LITTLE_ENDIAN_MODE);

	dsc_dma_start(p_sha_dev->pdev->io_base);

	ret = wait_for_completion_timeout(
			&p_sha_dev->pdev->completion,
			msecs_to_jiffies(200));
	reinit_completion(&p_sha_dev->pdev->completion);
	if (!ret) {
		dsc_ip_reset(p_sha_dev->pdev->reset_register,
					p_sha_dev->pdev->reset_bit);
		printk("sha wait timeout\n");

		return -ETIMEDOUT;
	}

	while (!sha_get_status(p_sha_dev->pdev->io_base));

	sha_clear_status(p_sha_dev->pdev->io_base);

	if (output) {
		for (i = 0; i <= digest_sel; i++) {
			sha_digest_select(p_sha_dev->pdev->io_base, i);
			*(unsigned int *)(output + i * sizeof(long)) =
					sha_get_digset_data(p_sha_dev->pdev->io_base);
		}
	} else {
		sha_get_int_value(p_sha_dev->pdev->io_base, p_sha_dev->iv);
	}

	mutex_unlock(&p_sha_dev->pdev->mutex);

	return 0;
}
