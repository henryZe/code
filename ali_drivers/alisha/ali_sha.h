/*
 * Security Hashing Algorithm driver
 * Copyright(C) 2015 ALi Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __ALI_SHA_H__
#define __ALI_SHA_H__

#include <linux/types.h>
#include <linux/mutex.h>
#include <crypto/sha.h>
#include <linux/interrupt.h>
#include <linux/delay.h>

#define ALI_SHA_MAX_DIGEST_SIZE (64)

#define MAX_SHA_FILE_SIZE_128MB (1<<27)

#define STAGE_FIRST_SEG		0
#define STAGE_INTER_SEG		1
#define STAGE_FINAL_SEG		2

#define SHA_NORMAL_MODE		0
#define SHA_SCATTER_MODE	1

enum SHA_MODE {
	SHA_SHA_1 = 0,//!< SHA1, HASH length is 20 bytes.
	SHA_SHA_224 = (1<<29),//!< SHA224, HASH length is 28 bytes. 
	SHA_SHA_256 = (2<<29),//!< SHA256, HASH length is 32 bytes.
	SHA_SHA_384 = (3<<29),//!< SHA384, HASH length is 48 bytes.
	SHA_SHA_512 = (4<<29),//!< SHA512, HASH length is 64 bytes.
};

struct ali_sha_dev_tag {
	struct mutex mutex;
	struct platform_device *clnt;
	unsigned int max_sha_size;
	void __iomem *io_base;
	int irq;
	unsigned long interrupt_flag;
	struct tasklet_struct done_task;
	struct work_struct done_work;
	struct completion completion;
	void __iomem *reset_register;
	unsigned char reset_bit;
};

struct ali_sha_hw_state {
	struct ali_sha_dev_tag *pdev;

	enum SHA_MODE sha_work_mode;
	unsigned char iv[64];
	unsigned char scatter_mode;
	unsigned char dma_stage;
	unsigned int block_length;
	unsigned int data_length;
	unsigned int total_length;
	unsigned char *residue;
	dma_addr_t residue_dma;
	unsigned int residue_length;
};

int sha_api_init(struct ali_sha_hw_state *p_sha_dev,
		unsigned int digestsize);
int sha_api_update(struct ali_sha_hw_state *p_sha_dev,
						unsigned char *input, dma_addr_t input_dma,
						unsigned int data_length);
int sha_api_digest(struct ali_sha_hw_state *p_sha_dev,
		unsigned char *output);
int sha_hal_digest(struct ali_sha_hw_state *p_sha_dev,
		dma_addr_t input, unsigned char *output);

#endif /*__ALI_SHA_H__*/
