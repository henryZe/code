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

#include <crypto/internal/hash.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/cryptohash.h>
#include <linux/types.h>
#include <crypto/sha.h>
#include <asm/byteorder.h>
#include <linux/device.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/of.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/highmem.h>

#include "ali_sha.h"
#include "sha_reg.h"

static struct ali_sha_dev_tag ali_sha_dev;

static int ali_sha_init(struct ahash_request *req)
{
	int ret = 0;
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct ali_sha_hw_state *dctx = ahash_request_ctx(req);

	memset(dctx, 0, sizeof(struct ali_sha_hw_state));

	dctx->pdev = &ali_sha_dev;

	ret = sha_api_init(dctx, crypto_ahash_digestsize(tfm));
	if (ret)
		return ret;

	return 0;
}

static int ali_sha_update(struct ahash_request *req)
{
	int ret, i, page_num;
	struct ali_sha_hw_state *dctx = ahash_request_ctx(req);
	unsigned char *input;
	unsigned int length;
	dma_addr_t input_dma;

	if (!dctx->pdev)
		return -ENODEV;

	dev_info(&dctx->pdev->clnt->dev,
		"%s, src: 0x%p, %d, dctx: 0x%p\n",
		__func__, req->src, req->nbytes, dctx);

	if (!req->src) {
		dev_info(&dctx->pdev->clnt->dev,
				"%s, req->src NULL\n", __func__);
		return -EFAULT;
	}

	page_num = sg_nents(req->src);

	ret = dma_map_sg(&dctx->pdev->clnt->dev,
		req->src, page_num, DMA_TO_DEVICE);
	if (ret != page_num)
		return -ENOMEM;

	/* HW constrains:
	*	In scatter mode, the first or the intermediate data block
	*	must be multiples of the Block-size(64/128 bytes).
	*	Otherwise the NO DMA interrupt occurs.
	*	So we need to check the data-len of each DMA operation.
	*/
	for (i = 0; i < page_num; i++) {
		input = kmap(sg_page(&req->src[i]));
		length = sg_dma_len(&req->src[i]);
		input_dma = sg_dma_address(&req->src[i]);

		ret = sha_api_update(dctx, input, input_dma, length);
		if (ret < 0) {
			dev_info(&dctx->pdev->clnt->dev,
				 "%s update error: %d\n", __func__, ret);
			return ret;
		}

		kunmap(sg_page(&req->src[i]));
	}

	dma_unmap_sg(&dctx->pdev->clnt->dev,
		req->src, page_num, DMA_TO_DEVICE);

	return ret;
}

static int ali_sha_final(struct ahash_request *req)
{
	int ret;
	struct ali_sha_hw_state *dctx = ahash_request_ctx(req);

	dev_info(&dctx->pdev->clnt->dev,
			"%s start\n", __func__);

	if (!req->result) {
		dev_info(&dctx->pdev->clnt->dev,
			"%s, req->result NULL\n", __func__);
		return -EFAULT;
	}

	ret = sha_api_digest(dctx, req->result);
	if (ret) {
		dev_info(&dctx->pdev->clnt->dev,
			 "%s error: %d\n", __func__, ret);
		return ret;
	}

	return 0;
}

static int ali_sha_finup(struct ahash_request *req)
{
	int ret;
	struct ali_sha_hw_state *dctx = ahash_request_ctx(req);

	if (!req->src || !req->result) {
		dev_info(&dctx->pdev->clnt->dev,
			 "%s, req->src or req->result NULL\n", __func__);

		ret = -EFAULT;
		goto out;
	}

	dev_info(&dctx->pdev->clnt->dev, "%s, %p, %d\n",
		 __func__, req->src, req->nbytes);

	ret = ali_sha_update(req);
	if (ret) {
		dev_info(&dctx->pdev->clnt->dev,
			 "%s error: %d\n", __func__, ret);
		goto out;
	}

	ret = ali_sha_final(req);
	if (ret) {
		dev_info(&dctx->pdev->clnt->dev,
			 "%s error: %d\n", __func__, ret);
		goto out;
	}

out:
	return ret;
}

static int ali_sha_all(struct ahash_request *req)
{
	int ret;
	struct ali_sha_hw_state *dctx = ahash_request_ctx(req);

	ret = ali_sha_init(req);
	if (ret) {
		dev_info(&dctx->pdev->clnt->dev,
			 "%s error: %d\n", __func__, ret);
		goto out;
	}

	dev_info(&dctx->pdev->clnt->dev, "%s start\n", __func__);

	ret = ali_sha_finup(req);
	if (ret) {
		dev_info(&dctx->pdev->clnt->dev,
			 "%s error: %d\n", __func__, ret);
		goto out;
	}

out:
	return ret;
}

static int ali_sha_cra_init(struct crypto_tfm *tfm)
{
	/* for ahash_request_ctx(req) size */
	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 sizeof(struct ali_sha_hw_state));

	return 0;
}

static int ali_sha_export(struct ahash_request *req, void *out)
{
	struct ali_sha_hw_state *dctx = ahash_request_ctx(req);
	struct ali_sha_hw_state *state = out;

	memcpy(state, dctx, sizeof(struct ali_sha_hw_state));

	if (dctx->residue_length) {
		state->residue = kzalloc(dctx->residue_length, GFP_KERNEL);
		memcpy(state->residue, dctx->residue, dctx->residue_length);
	}

	return 0;
}

static int ali_sha_import(struct ahash_request *req, const void *in)
{
	struct ali_sha_hw_state *dctx = ahash_request_ctx(req);
	const struct ali_sha_hw_state *state = in;

	memcpy(dctx, state, sizeof(struct ali_sha_hw_state));

	if (dctx->residue_length) {
		dctx->residue = dma_alloc_coherent(&dctx->pdev->clnt->dev,
				dctx->block_length, &dctx->residue_dma, GFP_KERNEL | GFP_DMA);
		memcpy(dctx->residue, state->residue, dctx->residue_length);
		kfree(state->residue);
	}

	return 0;
}

static struct ahash_alg ali_sha[] = {
	{
		.init = ali_sha_init,
		.update = ali_sha_update,
		.final = ali_sha_final,
		.finup = ali_sha_finup,
		.digest = ali_sha_all,
		.export = ali_sha_export,
		.import = ali_sha_import,
		.halg.digestsize = SHA1_DIGEST_SIZE,
		/* for export/import out/in args size */
		.halg.statesize = sizeof(struct ali_sha_hw_state),
		.halg.base = {
			.cra_name = "ali-sha1",
			.cra_driver_name = "ali-sha1",
			.cra_priority = 100,
			.cra_flags = CRYPTO_ALG_TYPE_AHASH | CRYPTO_ALG_ASYNC,
			.cra_blocksize = SHA1_BLOCK_SIZE,
			.cra_alignmask = 3,
			.cra_module = THIS_MODULE,
			.cra_init = ali_sha_cra_init,
		}
	},

	{
		.init = ali_sha_init,
		.update = ali_sha_update,
		.final = ali_sha_final,
		.finup = ali_sha_finup,
		.digest = ali_sha_all,
		.export = ali_sha_export,
		.import = ali_sha_import,
		.halg.digestsize = SHA224_DIGEST_SIZE,
		.halg.statesize = sizeof(struct ali_sha_hw_state),
		.halg.base = {
			.cra_name = "ali-sha224",
			.cra_driver_name = "ali-sha224",
			.cra_priority = 100,
			.cra_flags = CRYPTO_ALG_TYPE_AHASH | CRYPTO_ALG_ASYNC,
			.cra_blocksize = SHA224_BLOCK_SIZE,
			.cra_alignmask = 3,
			.cra_module = THIS_MODULE,
			.cra_init = ali_sha_cra_init,
		}
	},

	{
		.init = ali_sha_init,
		.update = ali_sha_update,
		.final = ali_sha_final,
		.finup = ali_sha_finup,
		.digest = ali_sha_all,
		.export = ali_sha_export,
		.import = ali_sha_import,
		.halg.digestsize = SHA256_DIGEST_SIZE,
		.halg.statesize = sizeof(struct ali_sha_hw_state),
		.halg.base = {
			.cra_name = "ali-sha256",
			.cra_driver_name = "ali-sha256",
			.cra_priority = 100,
			.cra_flags = CRYPTO_ALG_TYPE_AHASH | CRYPTO_ALG_ASYNC,
			.cra_blocksize = SHA256_BLOCK_SIZE,
			.cra_alignmask = 3,
			.cra_module = THIS_MODULE,
			.cra_init = ali_sha_cra_init,
		}
	},

	{
		.init = ali_sha_init,
		.update = ali_sha_update,
		.final = ali_sha_final,
		.finup = ali_sha_finup,
		.digest = ali_sha_all,
		.export = ali_sha_export,
		.import = ali_sha_import,
		.halg.digestsize = SHA384_DIGEST_SIZE,
		.halg.statesize = sizeof(struct ali_sha_hw_state),
		.halg.base = {
			.cra_name = "ali-sha384",
			.cra_driver_name = "ali-sha384",
			.cra_priority = 100,
			.cra_flags = CRYPTO_ALG_TYPE_AHASH | CRYPTO_ALG_ASYNC,
			.cra_blocksize = SHA384_BLOCK_SIZE,
			.cra_alignmask = 3,
			.cra_module = THIS_MODULE,
			.cra_init = ali_sha_cra_init,
		}
	},

	{
		.init = ali_sha_init,
		.update = ali_sha_update,
		.final = ali_sha_final,
		.finup = ali_sha_finup,
		.digest = ali_sha_all,
		.export = ali_sha_export,
		.import = ali_sha_import,
		.halg.digestsize = SHA512_DIGEST_SIZE,
		.halg.statesize = sizeof(struct ali_sha_hw_state),
		.halg.base = {
			.cra_name = "ali-sha512",
			.cra_driver_name = "ali-sha512",
			.cra_priority = 100,
			.cra_flags = CRYPTO_ALG_TYPE_AHASH | CRYPTO_ALG_ASYNC,
			.cra_blocksize = SHA512_BLOCK_SIZE,
			.cra_alignmask = 3,
			.cra_module = THIS_MODULE,
			.cra_init = ali_sha_cra_init,
		}
	},
};

static irqreturn_t ali_sha_irq(int irq, void *dev_id)
{
	struct ali_sha_dev_tag *psha = dev_id;

	/* get interrupt status */
	psha->interrupt_flag =
		dma_get_dma_status(psha->io_base);

	/* disable dma interrupt */
	dma_interrupt_disable_all(psha->io_base);

	/* clear sha status */
	if (sha_dma_get_dma_status(psha->io_base))
		sha_dma_clr_dma_status(psha->io_base);

	/* Or schedule_work */
	tasklet_schedule(&psha->done_task);
	schedule_work(&psha->done_work);

	return IRQ_HANDLED;
}

static void ali_sha_done_task(unsigned long data)
{
	struct ali_sha_dev_tag *psha = (struct ali_sha_dev_tag *)data;

	if (psha->interrupt_flag & DMA_TRANSFER_END_EVENT) {
		psha->interrupt_flag &= ~DMA_TRANSFER_END_EVENT;
		dma_clear_dma_status(psha->io_base, DMA_TRANSFER_END_EVENT);
		complete(&psha->completion);
	}
}

static void ali_sha_done_work(struct work_struct *work)
{
	struct ali_sha_dev_tag *psha = container_of(work, struct ali_sha_dev_tag, done_work);

	pr_info("work: ali_sha_done_work!!!!!!!!!!!!!\n");
	ssleep(10);

	schedule_work(&psha->done_work);
}

static int ali_sha_probe(struct platform_device *clnt)
{
	int i;
	int ret = -ENODEV;
	struct ali_sha_dev_tag *psha = &ali_sha_dev;
	struct resource *sha_res = NULL;

	dev_info(&clnt->dev, "ali_sha_probe start\n");

	memset(psha, 0, sizeof(struct ali_sha_dev_tag));
	mutex_init(&psha->mutex);
	psha->clnt = clnt;
	psha->max_sha_size = MAX_SHA_FILE_SIZE_128MB;

	dev_set_drvdata(&clnt->dev, psha);

	for (i = 0; i < ARRAY_SIZE(ali_sha); i++) {
		ret = crypto_register_ahash(&ali_sha[i]);
		if (ret) {
			dev_info(&clnt->dev,
				 "Ali SHA initialization failed.\n");
			return ret;
		}
	}


	/* Get the base address */
	sha_res = platform_get_resource(clnt, IORESOURCE_MEM, 0);
	if (!sha_res) {
		dev_info(&clnt->dev, "no MEM resource info.\n");
		return -ENODEV;
	}

	psha->io_base = devm_ioremap_resource(&clnt->dev, sha_res);
	if (IS_ERR(psha->io_base)) {
		dev_info(&clnt->dev, "can't ioremap.\n");
		return PTR_ERR(psha->io_base);
	} else {
		dev_info(&clnt->dev, "psha->io_base = %p.\n", psha->io_base);
	}

	/* Get reset register */
	sha_res = platform_get_resource(clnt, IORESOURCE_MEM, 1);
	if (!sha_res) {
		dev_info(&clnt->dev, "no MEM resource info.\n");
		return -ENODEV;
	}

	psha->reset_register = devm_ioremap_resource(&clnt->dev, sha_res);
	if (IS_ERR(psha->reset_register)) {
		dev_info(&clnt->dev, "can't ioremap.\n");
		return PTR_ERR(psha->reset_register);
	} else {
		dev_info(&clnt->dev, "psha->reset_register = %p.\n",
			psha->reset_register);
	}

	if (of_property_read_u8(psha->clnt->dev.of_node,
			"ip-reset", &psha->reset_bit)) {
		dev_info(&clnt->dev, "read ip-reset failed");
		return -EINVAL;
	}

	/* Get the IRQ */
	psha->irq = platform_get_irq(clnt, 0);
	if (psha->irq < 0) {
		dev_info(&clnt->dev, "no IRQ resource info.\n");
		return psha->irq;
	}

	ret = devm_request_irq(&clnt->dev, psha->irq, ali_sha_irq,
					IRQF_SHARED | IRQF_TRIGGER_HIGH,
					dev_name(&clnt->dev), psha);
	if (ret) {
		dev_info(&clnt->dev, "unable to request sha irq.\n");
		return -ENODEV;
	}

	/* Or INIT_WORK */
	INIT_WORK(&psha->done_work, ali_sha_done_work);
	tasklet_init(&psha->done_task, ali_sha_done_task,
					(unsigned long)psha);
	init_completion(&psha->completion);

	schedule_work(&psha->done_work);

	dev_info(&clnt->dev, "sha probed.\n");
	return 0;
}

static int ali_sha_remove(struct platform_device *clnt)
{
	int i;
	struct ali_sha_dev_tag *psha = dev_get_drvdata(&clnt->dev);

	if (!psha)
		return -ENODEV;

	for (i = 0; i < ARRAY_SIZE(ali_sha); i++)
		crypto_unregister_ahash(&ali_sha[i]);

	tasklet_kill(&psha->done_task);

	dev_info(&clnt->dev, "removed.\n");
	return 0;
}

static const struct of_device_id sha_matchtbl[] = {
	{ .name = "h_sha", .compatible = "alitech, h_sha" },
	{ }
};

static struct platform_driver sha_drv = {
	.probe = ali_sha_probe,
	.remove = ali_sha_remove,
	.driver = {
		.name = "h_sha",
		.of_match_table = sha_matchtbl,
		.owner = THIS_MODULE
	},
};

module_platform_driver(sha_drv);

MODULE_DESCRIPTION("Ali SHA algorithms support.");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ali");
MODULE_VERSION("1.2.0");
MODULE_ALIAS("Ali-sha");
