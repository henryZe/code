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

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/semaphore.h>
#include <linux/types.h>
#include <linux/uaccess.h>
#include <linux/dma-mapping.h>
#include <linux/highmem.h>
#include <linux/platform_device.h>

#include "ali_sha.h"

#define SHA1_BLOCK_SIZE 	64
#define SHA224_BLOCK_SIZE 	64
#define SHA256_BLOCK_SIZE 	64
#define SHA384_BLOCK_SIZE 	128
#define SHA512_BLOCK_SIZE 	128

int sha_api_init(struct ali_sha_hw_state *p_sha_dev, unsigned int digestsize)
{
	if (!p_sha_dev)
		return -EINVAL;

	switch (digestsize) {
	case SHA1_DIGEST_SIZE:
		p_sha_dev->sha_work_mode = SHA_SHA_1;
		p_sha_dev->block_length = SHA1_BLOCK_SIZE;
		break;
	case SHA224_DIGEST_SIZE:
		p_sha_dev->sha_work_mode = SHA_SHA_224;
		p_sha_dev->block_length = SHA224_BLOCK_SIZE;
		break;
	case SHA256_DIGEST_SIZE:
		p_sha_dev->sha_work_mode = SHA_SHA_256;
		p_sha_dev->block_length = SHA256_BLOCK_SIZE;
		break;
	case SHA384_DIGEST_SIZE:
		p_sha_dev->sha_work_mode = SHA_SHA_384;
		p_sha_dev->block_length = SHA384_BLOCK_SIZE;
		break;
	case SHA512_DIGEST_SIZE:
		p_sha_dev->sha_work_mode = SHA_SHA_512;
		p_sha_dev->block_length = SHA512_BLOCK_SIZE;
		break;
	default:
		return -EINVAL;
	}

	p_sha_dev->scatter_mode = SHA_SCATTER_MODE;
	p_sha_dev->residue = dma_alloc_coherent(&p_sha_dev->pdev->clnt->dev,
				p_sha_dev->block_length, &p_sha_dev->residue_dma,
				GFP_KERNEL | GFP_DMA);

	return 0;
}

int sha_api_update(struct ali_sha_hw_state *p_sha_dev,
						unsigned char *input, dma_addr_t input_dma,
						unsigned int data_length)
{
	int ret = 0;
	int pre_digest_length = 0;
	int new_input_offset = 0;
	int new_residue_length = 0;

	if (!p_sha_dev) {
		printk("Invalid device fd - NULL!\n");
		return -EINVAL;
	}

	if (!p_sha_dev->total_length)
		p_sha_dev->dma_stage = STAGE_FIRST_SEG;
	else
		p_sha_dev->dma_stage = STAGE_INTER_SEG;

	//logic
	{
		pre_digest_length = p_sha_dev->residue_length + data_length;

		//if new input is still not align block_size, then save in priv->residue
		if (pre_digest_length < p_sha_dev->block_length) {
			
			memcpy((void *)(p_sha_dev->residue + p_sha_dev->residue_length),
					input, data_length);

			p_sha_dev->residue_length = pre_digest_length;

			return 0;
		}
		//if there is residue existing, then add into residue for meeting the priv->block_length
		if (p_sha_dev->residue_length) {
			new_input_offset =
			    p_sha_dev->block_length - p_sha_dev->residue_length;

			memcpy(p_sha_dev->residue + p_sha_dev->residue_length,
					input, new_input_offset);

			p_sha_dev->residue_length = 0;
			p_sha_dev->data_length = p_sha_dev->block_length;
			p_sha_dev->total_length += p_sha_dev->block_length;
			ret = sha_hal_digest(p_sha_dev, p_sha_dev->residue_dma, NULL);
			if (ret)
				return ret;

			p_sha_dev->dma_stage = STAGE_INTER_SEG;
		} else {
			new_input_offset = 0;
		}

		//calculate the new residue length, and update priv->residue
		new_residue_length =
		    ((data_length - new_input_offset) % p_sha_dev->block_length);
		//add input to residue_input
		if (new_residue_length) {
			memcpy(p_sha_dev->residue,
			       input + data_length - new_residue_length,
			       new_residue_length);
		}
		//update the length
		p_sha_dev->residue_length = new_residue_length;
		p_sha_dev->data_length =
		    data_length - new_input_offset - new_residue_length;
		if (!p_sha_dev->data_length)
			return 0;

		p_sha_dev->total_length += p_sha_dev->data_length;

		ret = sha_hal_digest(p_sha_dev,
						input_dma + new_input_offset, NULL);
		if (ret)
			return ret;
	}

	return ret;
}

int sha_api_digest(struct ali_sha_hw_state *p_sha_dev,
		unsigned char *output)
{
	int ret = 0;

	if (!p_sha_dev) {
		printk("Invalid device fd - NULL!\n");
		return -EINVAL;
	}

	p_sha_dev->dma_stage = STAGE_FINAL_SEG;

	if (p_sha_dev->residue_length) {
		/* For dealing with the data less than block_length under scatter mode. */
		if (!p_sha_dev->total_length)
			p_sha_dev->scatter_mode = SHA_NORMAL_MODE;

		p_sha_dev->data_length = p_sha_dev->residue_length;
		p_sha_dev->total_length += p_sha_dev->residue_length;
		p_sha_dev->residue_length = 0;

		ret = sha_hal_digest(p_sha_dev, p_sha_dev->residue_dma, output);
	} else {
		p_sha_dev->data_length = 0;

		ret = sha_hal_digest(p_sha_dev, 0, output);
	}

	dma_free_coherent(&p_sha_dev->pdev->clnt->dev,
		p_sha_dev->block_length, p_sha_dev->residue,
		p_sha_dev->residue_dma);

	return ret;
}
