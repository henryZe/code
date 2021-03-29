#include "ali_sha.h"
#include "sha_reg.h"

unsigned char sha_dma_get_dma_status(void *base_addr)
{
    unsigned int temp = ioread32(base_addr + SHA_DMA_CTRL_REG);

    return ((temp & (1<<16))>>16);
}

void sha_dma_clr_dma_status(void *base_addr)
{
    unsigned int temp = ioread32(base_addr + SHA_DMA_CTRL_REG);
    
    iowrite32(temp | (1<<16), base_addr + SHA_DMA_CTRL_REG);
}

void dsc_ip_reset(void *reset_register, unsigned char reset_bit)
{
	iowrite32(ioread32(reset_register) | (1 << reset_bit), reset_register);
	msleep(100);
	iowrite32(ioread32(reset_register) & (~(1 << reset_bit)), reset_register);
}

void dma_clear_dma_status(void *base_addr,
		unsigned int dma_status)
{
    iowrite32(dma_status, base_addr + DMA_STATUS_REG);
}

unsigned char dma_get_dma_status(void *base_addr)
{
    unsigned char temp = ioread8(base_addr + DMA_STATUS_REG);
    
    return (temp & 0x33);
}

void dma_interrupt_disable_all(void *base_addr)
{
    iowrite32(((ioread32(base_addr + DMA_CTRL_REG)) & (~0x3300)),
			base_addr + DMA_CTRL_REG);
}

unsigned int get_dma_interrupt_enable_status(void *base_addr)
{
    return ((ioread32(base_addr + DMA_CTRL_REG) & 0x3300) >> 8);
}

void data_seq_set(void *base_address, enum DATA_SEQ data_seq)
{
    unsigned int data = (ioread32(base_address + DATA_KEY_SEQUENCE_REG));
    
    if (DATA_BIG_ENDIAN  ==  data_seq)
        iowrite32((data | 0x10), base_address + DATA_KEY_SEQUENCE_REG);
    else
        iowrite32((data & (~0x10)), base_address + DATA_KEY_SEQUENCE_REG);
}

void dma_src_addr_set(void *base_addr, dma_addr_t src)
{
	iowrite32(src, base_addr + DMA_START_ADDR_REG);
}

/*0x88*/
void dma_transfer_length_set(void *base_addr,
		unsigned int length, enum DMA_MODE mode)
{
	if ((PURE_DATA_MODE == mode) && (length > (1 << 30))) {	/*bigger than 1G, uint is byte */
		return;
	} else if ((TS_MODE == mode) && (length > (1 << 20))) {	/*bigger than 1M, uint is ts packet */
		return;
	}

	iowrite32(length, base_addr + DMA_LENGTH_REG);

	return;
}

void dma_dma_mode_select(void *base_addr, enum DMA_MODE mode)
{
	iowrite32((((ioread32(base_addr + DMA_CTRL_REG)) & (~(1 << 24))) | mode),
			base_addr + DMA_CTRL_REG);
}

void dma_data_target_select(void *base_addr,
		enum DMA_DATA_TARGET target)
{
	iowrite32((((ioread32(base_addr + DMA_CTRL_REG)) & (~(0xF << 17))) | target),
			base_addr + DMA_CTRL_REG);
}

void dsc_dma_start(void *base_addr)
{
	iowrite32(((ioread32(base_addr + DMA_CTRL_REG)) | (1 << 16)),
			base_addr + DMA_CTRL_REG);
}

void dma_interrupt_enable(void *base_addr, unsigned int int_flag)
{
	iowrite32(((ioread32(base_addr + DMA_CTRL_REG)) | int_flag),
			base_addr + DMA_CTRL_REG);
}

//1SHA block setting
/******************************SHA block setting*********************************/
/*0x300*/
void sha_mode_set(void *base_addr, enum SHA_MODE sha_mode)
{
	iowrite32((((ioread32(base_addr + SHA_CRTL_REG)) & (~0xE0000000)) | sha_mode),
			base_addr + SHA_CRTL_REG);
}

void sha_data_source_select(void *base_addr, unsigned int sel)
{
	/*0: from Dram DMA
	   1:  from flash DMA */
	iowrite32((((ioread32(base_addr + SHA_CRTL_REG)) & (~0x6)) | sel << 1),
			base_addr + SHA_CRTL_REG);
}

/**0x304**/
void sha_clear_status(void *base_addr)
{
	iowrite32(1, base_addr + SHA_STATUS_REG);
}

/**0x314**/
unsigned int sha_get_digset_data(void *base_addr)
{
	return (ioread32(base_addr + SHA_DIGEST_PORT_REG));
}

/*0x318*/
void sha_digest_select(void *base_addr, unsigned int sel)
{
	/*
	   0-4:  for sha-1(160bits)
	   0-7:  for sha-256
	   0-b:  for sha-384
	   0-f :  for sha-512
	 */

	/*  0 ~ 4: for SHA-1 (160 bits)
	   0 ~ 6: for SHA-224 (224 bits)
	   0 ~ 7: for SHA-256 (256 bits)
	   0 ~ B: for SHA-384 (384 bits)
	   0 ~ F: for SHA-512 (512 bits)
	 */
	iowrite32(((ioread32(base_addr + SHA_DIGEST_ADDR_REG) & 0x30) | sel),
			base_addr + SHA_DIGEST_ADDR_REG);
}

/*0x318*/
void sha_endian_select(void *base_addr, unsigned int sel)
{
	/*Bit 4 */
	/*0: big_endian
	   1: little_endian
	 */
	if (SHA_BIG_ENDIAN_MODE == sel) {
		iowrite32((ioread32(base_addr + SHA_DIGEST_ADDR_REG) & (~0x10)),
				base_addr + SHA_DIGEST_ADDR_REG);
	} else {
		iowrite32((ioread32(base_addr + SHA_DIGEST_ADDR_REG) | 0x10),
				base_addr + SHA_DIGEST_ADDR_REG);
	}
}

/*0x320*/
void sha_set_scatter_mode(void *base_addr, unsigned char scatter_mode)
{
	scatter_mode &= 0x01;

	iowrite32(((ioread32(base_addr + SHA_DMA_CTRL_REG)) & 0xBFFFFFFF) | (scatter_mode << 30),
				base_addr + SHA_DMA_CTRL_REG);
}

void sha_set_dma_stage(void *base_addr, unsigned char dma_stage)
{
	dma_stage &= 0x03;

	iowrite32(((ioread32(base_addr + SHA_DMA_CTRL_REG)) & 0xCFFFFFFF) | (dma_stage << 28),
				base_addr + SHA_DMA_CTRL_REG);
}

void sha_set_total_len(void *base_addr, unsigned int total_len)
{
	iowrite32(total_len, base_addr + SHA_DMA_TOTAL_LEN);
}

void sha_set_int_value(void *base_addr, unsigned char * iv)
{
	unsigned int *p = (unsigned int *) iv;

	iowrite32(p[0], base_addr + SHA_INT_VALUE_H0_L);
	iowrite32(p[1], base_addr + SHA_INT_VALUE_H0_H);
	iowrite32(p[2], base_addr + SHA_INT_VALUE_H1_L);
	iowrite32(p[3], base_addr + SHA_INT_VALUE_H1_H);
	iowrite32(p[4], base_addr + SHA_INT_VALUE_H2_L);
	iowrite32(p[5], base_addr + SHA_INT_VALUE_H2_H);
	iowrite32(p[6], base_addr + SHA_INT_VALUE_H3_L);
	iowrite32(p[7], base_addr + SHA_INT_VALUE_H3_H);
	iowrite32(p[8], base_addr + SHA_INT_VALUE_H4_L);
	iowrite32(p[9], base_addr + SHA_INT_VALUE_H4_H);
	iowrite32(p[10], base_addr + SHA_INT_VALUE_H5_L);
	iowrite32(p[11], base_addr + SHA_INT_VALUE_H5_H);
	iowrite32(p[12], base_addr + SHA_INT_VALUE_H6_L);
	iowrite32(p[13], base_addr + SHA_INT_VALUE_H6_H);
	iowrite32(p[14], base_addr + SHA_INT_VALUE_H7_L);
	iowrite32(p[15], base_addr + SHA_INT_VALUE_H7_H);
}

unsigned int sha_get_status(void *base_addr)
{
    return ((ioread32(base_addr + SHA_STATUS_REG)) & 1);
}

void sha_get_int_value(void *base_addr, unsigned char *iv)
{
	unsigned int *p = (unsigned int *)iv;

	p[0] = ioread32(base_addr + SHA_INT_VALUE_H0_L);
	p[1] = ioread32(base_addr + SHA_INT_VALUE_H0_H);
	p[2] = ioread32(base_addr + SHA_INT_VALUE_H1_L);
	p[3] = ioread32(base_addr + SHA_INT_VALUE_H1_H);
	p[4] = ioread32(base_addr + SHA_INT_VALUE_H2_L);
	p[5] = ioread32(base_addr + SHA_INT_VALUE_H2_H);
	p[6] = ioread32(base_addr + SHA_INT_VALUE_H3_L);
	p[7] = ioread32(base_addr + SHA_INT_VALUE_H3_H);
	p[8] = ioread32(base_addr + SHA_INT_VALUE_H4_L);
	p[9] = ioread32(base_addr + SHA_INT_VALUE_H4_H);
	p[10] = ioread32(base_addr + SHA_INT_VALUE_H5_L);
	p[11] = ioread32(base_addr + SHA_INT_VALUE_H5_H);
	p[12] = ioread32(base_addr + SHA_INT_VALUE_H6_L);
	p[13] = ioread32(base_addr + SHA_INT_VALUE_H6_H);
	p[14] = ioread32(base_addr + SHA_INT_VALUE_H7_L);
	p[15] = ioread32(base_addr + SHA_INT_VALUE_H7_H);
}
