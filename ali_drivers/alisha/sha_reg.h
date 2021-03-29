#ifndef _DES_M3602_REG_H_
#define _DES_M3602_REG_H_

#include <asm/io.h>

#define	DSC_IRQ_ID_S3922 		(OS_IRQ_OFFSET + 32 + 13)

/*for interrupt positon*/
#define TS_TARGET_ADDR_ERROR_EVENT  0x20
#define DMA_TRANSFER_END_EVENT  0x10

#ifndef ARM_AS
#define  	DSC_BASE_ADDR_S3602F    0xb8034000
#define 	DSC_BASE_ADDR_M3603     0xb803a000
#define   IP_CORE_RESET_CTRL_M3281 0xb8000060
#define   IP_CORE_RESET_CTRL_M36XX 0xb8000084
#define 	IC_MEM_PRIV_START	0xb8041010
#define 	IC_MEM_PRIV_END		0xb8041014
#define 	IC_MEM_PRIV_START_C3922	0xb80100A0
#define 	IC_MEM_PRIV_END_C3922 0xb80100A4
#define  OTP_IOBASE_M32 0xb8000100
#define  OTP_IOBASE_M37 0xb8042000
#define 	IP_CORE_RESET_CTRL_S3922 0xb8000268
#define     IP_CORE_RESET_CTRL_C3922 0xb8084c00
#else
#define  	DSC_BASE_ADDR_S3602F    0x18034000
#define 	DSC_BASE_ADDR_M3603     0x1803a000
#define   IP_CORE_RESET_CTRL_M3281 0x18000060
#define   IP_CORE_RESET_CTRL_M36XX 0x18000084
#define 	IC_MEM_PRIV_START	0x18041010
#define 	IC_MEM_PRIV_END		0x18041014
#define 	IC_MEM_PRIV_START_C3922	0x180100A0
#define 	IC_MEM_PRIV_END_C3922 0x180100A4
#define OTP_IOBASE_M32 0x18000100
#define OTP_IOBASE_M37 0x18042000
#define 	IP_CORE_RESET_CTRL_S3922 0x18000268
#define     IP_CORE_RESET_CTRL_C3922 0x18084c00
#endif

#define		DSC_BASE_ADDR_DEFAULT	DSC_BASE_ADDR_S3602F
#define 	DSC_BASE_ADDR_M3281		DSC_BASE_ADDR_M3603
#define		DSC_BASE_ADDR_M3701		DSC_BASE_ADDR_S3602F
#define 	DSC_BASE_ADDR_M3811		DSC_BASE_ADDR_M3603
#define		DSC_BASE_ADDR_C3503		DSC_BASE_ADDR_S3602F
#define		DSC_BASE_ADDR_C3821		DSC_BASE_ADDR_S3602F
#define		DSC_BASE_ADDR_M3921		DSC_BASE_ADDR_S3602F

#define 	IP_CORE_RESET_CTRL_M3701 IP_CORE_RESET_CTRL_M36XX
#define 	IP_CORE_RESET_CTRL_C3503 IP_CORE_RESET_CTRL_M36XX
#define 	IP_CORE_RESET_CTRL_C3821 IP_CORE_RESET_CTRL_M36XX
#define 	IP_CORE_RESET_CTRL_M3921 IP_CORE_RESET_CTRL_M36XX

#define     DSC_CORE_RESET_BIT_M3281 19
#define     DSC_CORE_RESET_BIT_M36XX 16
#define     DSC_CORE_RESET_BIT_M3701 DSC_CORE_RESET_BIT_M36XX
#define     DSC_CORE_RESET_BIT_C3503 DSC_CORE_RESET_BIT_M36XX
#define     DSC_CORE_RESET_BIT_C3821 DSC_CORE_RESET_BIT_M36XX
#define     DSC_CORE_RESET_BIT_M3921 DSC_CORE_RESET_BIT_M36XX
#define     DSC_CORE_RESET_BIT_S3922 1
#define     DSC_CORE_RESET_BIT_C3922 0

#define OTP_02_VALUE_M37 0x40
#define OTP_03_VALUE_M37 0x44
#define OTP_82_VALUE_M37 0x6c
#define OTP_DC_VALUE_M37 0x78
#define OTP_DD_VALUE_M37 0x7c
#define OTP_8C_VALUE_M37 0x90

#define OTP_02_VALUE_M32 0x24
#define OTP_03_VALUE_M32 0x28

/*#define IS_CHAINING_IV(blen) ((PURE_DATA_MODE == priv->dma_mode) && (data_length >= blen) \
        && ((KEY_FROM_SRAM == priv->key_info.key_from) || (KEY_FROM_CRYPTO == priv->key_info.key_from)))
#define _IS_CHAINING_IV(blen) ((PURE_DATA_MODE == priv->dma_mode) && (data_length >= blen) \
        && ((KEY_FROM_SRAM == priv->key_hdl[0].key_from) || (KEY_FROM_CRYPTO == priv->key_hdl[0].key_from))) */

/*
    valid addr is:
        located at [0x8000_0000, 0xAFFF_FFFC]
        aligned with 4 bytes

      valid - return 1;
    invalid - return 0;
    
*/
#define IS_VALID_ADDR(addr) (((addr) >= 0x80000000) && ((addr) <= 0xAFFFFFFC) && (!((addr) & 0x03)))

/*Dma control register=0x90*/
#define DMA_START_BIT  (1<<16)
#define TS_TARGET_ADDR_ERROR_EN  (1<<13)
#define DMA_TRANSFER_END_CHECK_EN  (1<<12)
#define PID_NOT_IN_LIST_CHECK_EN    (1<<9)
#define DMA_SYNC_BYTE_CHECK_EN      (1<<8)

/*DMA status 0x94*/
#define HMAC_DIGEST_READY  (1<<2)
#define DMA_TRANSFER_END  (1<<4)
#define DMA_TARGET_ADDR_ERROR  (1<<5)
#define SHA_DIGEST_FINISH_EVENT (1<<7)
#define DMA_TRANSFER_BUSY  (1<<8)
#define AES_CPU_IO_BUSY (1<<13)
#define DMA_TRANSFER_FINISH  (1<<15)

#define  KEY_MODE_FROM_SRAM 0
#define  KEY_MODE_FROM_REG  1
#define  KEY_MODE_FROM_OTP  2
#define SEC_KEY_FROM_DES  0
#define SEC_KEY_FROM_CRYPTO 1
#define SEC_DMA_TRANSFER_MODE  1
#define SEC_CPU_TRANSFER_MODE   0
#define SECURITY_DATA_TIMEOUT   1000*12	//1000*12 64MB max

/*sha dma status*/
#define SHA_DMA_IS_BUSY 1

#define AES_BLOCK_LENGTH  16	/*bytes */
#define DES_BLOCK_LENGTH  8	/*bytes */

#define SHA_LITTLE_ENDIAN_MODE  1
#define SHA_BIG_ENDIAN_MODE  0

#define SHA_WORD_SWAP_MODE 1
#define SHA_WORD_NSWAP_MODE 0

#define DSC_IMB_FREE_STATUS         0
#define DSC_IMB_WRITE_STATUS        1
#define DSC_IMB_READ_STATUS         2
#define DSC_PID_NOT_FOUND_STATUS    3
#define DSC_PID_NOT_SET             4

#define ROTL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define BYTESWAP1(x) ((ROTR((x), 8) & 0xff00ff00L) | (ROTL((x), 8) & 0x00ff00ffL))
//#define BYTESWAP(x)(x)
#define BYTESWAP(x) ((ROTR((x), 8) & 0xff00ff00L) | (ROTL((x), 8) & 0x00ff00ffL))

#define SWAP(x) ((ROTL(x, 8) & 0x00ff00ff) | (ROTR(x, 8) & 0xff00ff00))
#define GETU32(p) SWAP(*((unsigned int *)(p)))
#define PUTU32(ct, st) \
    { \
        *((unsigned int *)(ct)) = SWAP((st)); \
    }

#ifdef __cplusplus
extern "C" {
#endif

/* M3602 register define */
enum ALI_DSC_REG_ENUM {
	KEY_MODE_REG = 0,
	/*key mode setting */
	PID_RAM_RW_REG = 0x4,
	PID_RAM_WR_DATA_REG_DATA0 = 0x8,
	PID_RAM_WR_DATA_REG_DATA1 = 0x38,
	PID_RAM_WR_DATA_REG_DATA2 = 0x34,	//introduced from Cap210
	PID_RAM_RD_DATA_REG_DATA0 = 0xc,
	PID_RAM_RD_DATA_REG_DATA1 = 0x3c,
	PID_RAM_RD_DATA_REG_DATA2 = 0x44,
	KEY_RAM_RW_REG = 0x10,
	KEY_RAM_WR_DATA_REG1 = 0x14,
	KEY_RAM_WR_DATA_REG2 = 0x18,
	KEY_RAM_WR_DATA_REG3 = 0x1c,
	KEY_RAM_WR_DATA_REG4 = 0x20,
	KEY_RAM_RD_DATA_REG1 = 0x24,
	KEY_RAM_RD_DATA_REG2 = 0x28,
	KEY_RAM_RD_DATA_REG3 = 0x2c,
	KEY_RAM_RD_DATA_REG4 = 0x30,
	CSA_REG = 0x40,
	DCW_REG1 = 0x48,
	DCW_REG2 = 0x4c,
	DATA_KEY_SEQUENCE_REG = 0x50,
	RESIDUE_INFO_RAM_RW_CTRL = 0x54,
	RESIDUE_INFO_RAM_WR_DATA0 = 0x58,
	RESIDUE_INFO_RAM_WR_DATA1 = 0x5c,
	RESIDUE_INFO_RAM_WR_DATA2 = 0x60,
	RESIDUE_INFO_RAM_WR_DATA3 = 0x64,
	RESIDUE_INFO_RAM_WR_DATA4 = 0x68,
	RESIDUE_INFO_RAM_RD_DATA0 = 0x6c,
	RESIDUE_INFO_RAM_RD_DATA1 = 0x70,
	RESIDUE_INFO_RAM_RD_DATA2 = 0x74,
	RESIDUE_INFO_RAM_RD_DATA3 = 0x78,
	RESIDUE_INFO_RAM_RD_DATA4 = 0x7c,
	CSA3_DCW0_REG = 0x60,
	CSA3_DCW1_REG = 0x64,
	CSA3_DCW2_REG = 0x68,
	CSA3_DCW3_REG = 0x6c,
	/*DMA Block Register */

	DMA_START_ADDR_REG = 0x80,
	/*dma start address */
	DMA_TARGET_ADDR_REG = 0x84,
	/*dma target address */
	DMA_LENGTH_REG = 0x88,
	/*dma length address */
	CURRENT_DMA_ADDR_REG = 0x8c,
	/*current dma address */
	DMA_CTRL_REG = 0x90,
	/*dma control register */
	DMA_STATUS_REG = 0x94,
	/*dma status register */

	IMB_STATUS_REG = 0x98,
	DMA_CURR_RD_ADDR_REG = 0x9c,
	RD_QWORD_COUNTER_REG = 0xa0,
	WR_QWORD_COUNTER_REG = 0xa4,
	MEMBUS_PRIORITY_SET_REG = 0xa8,

	DSC_PRIV_MEM_START = 0xc0,
	DSC_PRIV_MEM_END = 0xc4,

	/* For command queue */
	DSC_CMDQ_ID = 0xD0,
	DSC_CMDQ_BASE_ADDR = 0xD4,
	DSC_CMDQ_EN_LENGTH = 0xD8,
	DSC_CMDQ_RD_WR_PTR = 0xDC,
	DSC_CMDQ_INT_STATUS = 0xE0,

	/*Triple DES block registers */
	TDES_CTRL_REG = 0x100,
	/*3des control register */
	TDES_STATUS_REG = 0x104,
	/*3des status register */

	TDES_DATA_IN0_REG = 0x110,
	TDES_DATA_IN1_REG = 0x114,
	TDES_DATA_OUT0_REG = 0x118,
	TDES_DATA_OUT1_REG = 0x11c,
	TDES_IV0_REG = 0x120,
	TDES_IV1_REG = 0x124,
	TDES_KEYA_ODD0_REG = 0x128,
	TDES_KEYA_ODD1_REG = 0x12c,
	TDES_KEYA_EVEN0_REG = 0x130,
	TDES_KEYA_EVEN1_REG = 0x134,
	TDES_KEYB_ODD0_REG = 0x138,
	TDES_KEYB_ODD1_REG = 0x13c,
	TDES_KEYB_EVEN0_REG = 0x140,
	TDES_KEYB_EVEN1_REG = 0x144,
	TDES_KEYC_ODD0_REG = 0x148,
	TDES_KEYC_ODD1_REG = 0x14c,
	TDES_KEYC_EVEN0_REG = 0x150,
	TDES_KEYC_EVEN1_REG = 0x154,

	/*AES  block registers */
	AES_CTRL_REG = 0x200,
	AES_STATUS_REG = 0x204,
	AES_INC_REG = 0x208,
	/*AES increment value for counter mode register */
	AES_DATA_IN0_REG = 0x210,
	AES_DATA_IN1_REG = 0x214,
	AES_DATA_IN2_REG = 0x218,
	AES_DATA_IN3_REG = 0x21c,
	AES_DATA_OUT0_REG = 0x220,
	AES_DATA_OUT1_REG = 0x224,
	AES_DATA_OUT2_REG = 0x228,
	AES_DATA_OUT3_REG = 0x22c,
	AES_IV0_REG = 0x230,
	AES_IV1_REG = 0x234,
	AES_IV2_REG = 0x238,
	AES_IV3_REG = 0x23c,
	AES_ODD_KEY0_REG = 0x240,
	AES_ODD_KEY1_REG = 0x244,
	AES_ODD_KEY2_REG = 0x248,
	AES_ODD_KEY3_REG = 0x24c,
	AES_ODD_KEY4_REG = 0x250,
	AES_ODD_KEY5_REG = 0x254,
	AES_ODD_KEY6_REG = 0x258,
	AES_ODD_KEY7_REG = 0x25c,
	AES_EVEN_KEY0_REG = 0x260,
	AES_EVEN_KEY1_REG = 0x264,
	AES_EVEN_KEY2_REG = 0x268,
	AES_EVEN_KEY3_REG = 0x26c,
	AES_EVEN_KEY4_REG = 0x270,
	AES_EVEN_KEY5_REG = 0x274,
	AES_EVEN_KEY6_REG = 0x278,
	AES_EVEN_KEY7_REG = 0x27c,
	AES_COUNTER0_REG = 0x280,
	AES_COUNTER1_REG = 0x284,
	AES_COUNTER2_REG = 0x288,
	AES_COUNTER3_REG = 0x28c,

	/*SHA block registers */
	SHA_CRTL_REG = 0x300,
	SHA_STATUS_REG = 0x304,
	SHA_FLASH_DMA_ADDR_REG = 0x308,
	/*sha flash dma start address */

	SHA_FLASH_DMA_LENGTH_REG = 0x30c,
	SHA_DMA_STATUS_REG = 0x310,
	SHA_DIGEST_PORT_REG = 0x314,
	/*the digest output port register */
	SHA_DIGEST_ADDR_REG = 0x318,
	/*the address used to select the digest section output via the DIGEST output port */

	SHA_DMA_CTRL_REG = 0x320,
	SHA_DMA_ADDR_REG = 0x324,
	SHA_DMA_LENGTH_REG = 0x328,
	SHA_DMA_TOTAL_LEN = 0x32c,

	SHA_INT_VALUE_H0_L = 0x330,
	SHA_INT_VALUE_H0_H = 0x334,
	SHA_INT_VALUE_H1_L = 0x338,
	SHA_INT_VALUE_H1_H = 0x33c,
	SHA_INT_VALUE_H2_L = 0x340,
	SHA_INT_VALUE_H2_H = 0x344,
	SHA_INT_VALUE_H3_L = 0x348,
	SHA_INT_VALUE_H3_H = 0x34c,
	SHA_INT_VALUE_H4_L = 0x350,
	SHA_INT_VALUE_H4_H = 0x354,
	SHA_INT_VALUE_H5_L = 0x358,
	SHA_INT_VALUE_H5_H = 0x35c,
	SHA_INT_VALUE_H6_L = 0x360,
	SHA_INT_VALUE_H6_H = 0x364,
	SHA_INT_VALUE_H7_L = 0x368,
	SHA_INT_VALUE_H7_H = 0x36c,

	HMAC_CONTROL_REG = 0x800,
	HMAC_STATUS_REG = 0x804,
	HMAC_DIGEST_PORT_REG = 0x814,
	HMAC_DIGEST_SEL_REG = 0x818,
	HMAC_KEY_0_REG = 0x820,
	HMAC_KEY_1_REG = 0x824,
	HMAC_KEY_2_REG = 0x828,
	HMAC_KEY_3_REG = 0x82C,
};

/* For HW_CHECK_IP */
enum HW_CHK_REG {
	HW_CHK_GLOBAL_CONFIG = 0,
	HW_CHK_INDEX = 0x4,
	HW_CHK_CONFIG = 0x8,
	HW_CHK_TRIGGER = 0xC,
	HW_CHK_STATUS = 0x10,
	HW_CHK_DEBUG = 0x14,
	HW_CHK_HASH_ERROR = 0x18,
	HW_CHK_DATA_RIGHT = 0x1C,
	HW_CHK_START_ADDR = 0x20,
	HW_CHK_DATA_LENGTH = 0x24,
	HW_CHK_INTERVAL_SET = 0x28,
	HW_CHK_MEM_LATENCY = 0xA0,

	HW_CHK_BASE = 0xb8020000,
	HW_CHK_RESET_CTRL = 0xb8000084,
	HW_CHK_RESET_BIT = 27,

	HW_CHK_RESET_CTRL_CAP210 = 0xb8000080,
	HW_CHK_RESET_BIT_CAP210 = 4,

	HW_CHK_RESET_CTRL_S3922 = 0xb8000268,
	HW_CHK_RESET_BIT_S3922 = 6,

	HW_CHK_RESET_CTRL_C3922 = 0xb8084c00,
	HW_CHK_RESET_BIT_C3922 = 0,
};

enum STREAM_ID {
	TS_ID = 0,
	PURE_ID = (1 << 2),
};

enum DMA_DATA_TARGET {
	DMA_DATA_TARGET_IS_3DES = 0,
	DMA_DATA_TARGET_IS_AES = (1 << 17),
	DMA_DATA_TARGET_IS_SHA = (2 << 17),
	DMA_DATA_TARGET_IS_CSA = (3 << 17),
	DMA_DATA_TARGET_IS_CSA3 = (4 << 17),
	DMA_DATA_TARGET_IS_HMAC = (8 << 17),
};

enum DES_TDES_MODE {
	DES_MODE_IS_DES = (1 << 16),
	DES_MODE_IS_3DES = (0),
};

enum EN_DECRYPT_MODE {
	ENCRYPT_E_FOR_DES = 0,
	DECRYPT_D_FOR_DES = (1 << 8),
	ENCRYPT_EDE_FOR_3DES = 0,
	DECRYPT_DED_FOR_3DES = (1 << 8),
};

enum CRYPT_MODE {
	ENCRYPT_MODE = 0,
	DECRYPT_MODE = (1 << 8),
};

enum DATA_SOURCE {
	DES_DATA_SOURCE_IS_CPU = 0,
	DES_DATA_SOURCE_IS_DMA = (1 << 2),
};

enum AES_DATA_SOURCE {
	AES_DATA_SOURCE_IS_CPU = 0,
	AES_DATA_SOURCE_IS_DMA = (1 << 2),
};

enum AES_KEY_SIZE {
	AES_KEY_SIZE_128_BITS = 0,
	AES_KEY_SIZE_192_BITS = (1 << 9),
	AES_KEY_SIZE_256_BITS = (2 << 9),
};

enum AES_CIPHER_MODE {
	AES_ENCRYPT_CIPHER = 0,
	AES_DECRYPT_INV_CIPHER = (1 << 8),
};

enum DSC_KEY_IV {
	DSC_KEY2RAM,
	DSC_IV2RAM = 1 << 24,
};

enum DATA_SEQ {
	DATA_BIG_ENDIAN = 1,
	DATA_LITTLE_ENDIAN = 0
};

enum KEY_SEQ {
	KEY_BIG_ENDIAN = 1,
	KEY_LITTLE_ENDIAN = 0
};

enum RAM_KEY_TYPE {
	DEFAULT_KEY = 0,
	ODD_KEY = 1,
	EVEN_KEY = 2,
};

enum dsc_cmdq_cmdtype {
	DSC_IO_READ,
	DSC_IO_WRITE,
	DSC_IO_CHECK = 4,
};

enum key_size_byte {
	DSC_KEY_SIZE_BYTE_8 = 0,
	DSC_KEY_SIZE_BYTE_16,
	DSC_KEY_SIZE_BYTE_24,
	DSC_KEY_SIZE_BYTE_32,
};

enum residue_handle_mode {
	DSC_RESIDUE_CLEAR = 0,
	DSC_RESIDUE_AS_ATSC,
	DSC_RESIDUE_HW_CTS,
	DSC_RESIDUE_CTR_HDL,
};

enum data_continuous_mode {
	DSC_INDEPENDENT_MODE = 0,
	DSC_CONTINUOUS_MODE1,
	DSC_CONTINUOUS_MODE2,
};

enum pid_ram_algo_select {
	DSC_ALGO_AES = 0,
	DSC_ALGO_DES = 1,
	DSC_ALGO_TDES = 2,
	DSC_ALGO_CSA1 = 3,
	DSC_ALGO_CSA2 = 4,
	DSC_ALGO_CSA3 = 5,
	DSC_ALGO_HMAC = 0xE,
};

typedef struct PID_RAM_INFO {
	unsigned int key_addr:8;
	unsigned int pid_value:13;
	unsigned int stream_id:8;
	unsigned int pid_map_enable:1;
	unsigned int mixed_ck_addr:8;
	unsigned int even_is_ck:1;	//(even key from AKL?)
	unsigned int odd_is_ck:1;	//(odd key from AKL?)
	unsigned int changed:1;
	unsigned int kl_sel:4;
	unsigned int raw_ts:1;	// raw[0], ts[1]
	unsigned int continuous_mode:2;	// Independent[00], Continuous[01]
	unsigned int sel_algo:4;	// AES[0000], TDES[0001], CSAv3[1001], CSAv2[1010]
	unsigned int sel_keysize:2;	// 64bits[00], 128bits[01], 192bits[10], 256bit[11]
	unsigned int sel_chaining:3;	// CBC[000], ECB[001], OFB[010], CFB[011], CTR[100]
	unsigned int sel_residue:3;	// NoHandle[000], ATIS[001], CTS[010], CTR[011], Note[100]
	unsigned int iv_addr:7;
	unsigned int reserved:29;
} PID_RAM_INFO, *pPID_RAM_INFO;

typedef struct PID_RAM_INFO_DATA0 {
	unsigned int key_addr:5;
	unsigned int pid_value:13;
	unsigned int stream_id:3;
	unsigned int pid_map_enable:1;
	unsigned int stream_id_ex:1;
	unsigned int key_addr_ex:1;
	unsigned int mixed_ck_addr:6;
	unsigned int even_is_ck:1;	//(even key from AKL?)
	unsigned int odd_is_ck:1;	//(odd key from AKL?)
} PID_RAM_INFO_DATA0;

typedef struct PID_RAM_INFO_DATA1 {
	unsigned int key_addr_ex:2;	// [0:1]
	unsigned int rsvd1:2;	// [2:3]
	unsigned int kl_sel:4;	// [4:7] kl_1[000],kl_2[001],kl_3[010],kl_4[011],kl_5[100],kl_6[101]
	unsigned int mixed_ck_addr_ex:2;	// [8:9]
	unsigned int rsvd2:2;	// [10:11]
	unsigned int raw_ts:1;	// [12] raw-data[0], ts-data[1]
	unsigned int continuous_mode:2;	// [13:14]
	unsigned int rsvd3:1;	// [15]
	unsigned int stream_id_4_7:4;	// [16:19] Higg 4bits of stream ID
	unsigned int sel_algo:4;	// [20:23]. AES[0000], TDES[0001], CSAv3[1001], CSAv2[1010]
	unsigned int sel_keysize:2;	// [24:25]. 64bits[00], 128bits[01], 192bits[10], 256bit[11]
	unsigned int sel_chaining:3;	// [26:28]. CBC[000], ECB[001], OFB[010], CFB[011], CTR[100]
	unsigned int sel_residue:3;	// [29:31]. NoHandle[000], ATIS[001], CTS[010], CTR[011], Note[100]
} PID_RAM_INFO_DATA1;

typedef struct PID_RAM_INFO_DATA2 {
	unsigned int iv_addr:7;	// [0:6]
	unsigned int rsvd:25;	// [7:31]
} PID_RAM_INFO_DATA2;

union hmac_control_union {
	unsigned int data;
	struct {
		unsigned int hmac_work_mode:3;	// [0:2]
		unsigned int rsvd:29;	// [31:3]
	} u;
};

union hmac_status_union {
	unsigned int data;
	struct {
		unsigned int hmac_digest_ready:1;	// [0]
		unsigned int rsvd:31;	// [31:1]
	} u;
};

union hmac_digest_sel {
	unsigned int data;
	struct {
		unsigned int hmac_digest_sel:4;	// [0:3]
		unsigned int rsvd:28;	// [31:4]
	} u;
};

union key_mode_setting_union {
	unsigned int data;
	struct {
		unsigned int key_mode:1;	// [0]
		unsigned int otp_key_mode:1;	// [1]
		unsigned int rsvd0:2;	// [2:3]
		unsigned int secure_key_mode:1;	// [4]
		unsigned int rsvd1:3;	// [5:7]
		unsigned int key_mapping_mode:2;	// [8:9]
		unsigned int rsvd2:6;	// [10:15]
		unsigned int stream_id:8;	// [16:23]
		unsigned int rsvd3:6;	// [24:27]
		unsigned int key_location_sel_en:1;	// [28]
		unsigned int rsvd4:3;	// [31:29]
	} u;
};

union pid_ram_data0_union {
	unsigned int data;
	PID_RAM_INFO_DATA0 u;
};

union pid_ram_data1_union {
	unsigned int data;
	PID_RAM_INFO_DATA1 u;
};

union pid_ram_ctrl_union {
	unsigned int data;
	struct {
		unsigned int pid_ram_wr_start:1;	// [0]
		unsigned int rsvd0:3;	// [1:3]
		unsigned int pid_ram_rd_start:1;	// [4]
		unsigned int rsvd1:3;	// [5:7]
		unsigned int pid_ram_addr:7;	// [8:14]
		unsigned int rsvd2:1;	// [15]
		unsigned int otp_read_trigger:1;	// [16]
		unsigned int otp_key_addr:1;	// [17]
		unsigned int dsc_ski_busy:1;	// [18]
		unsigned int otp_key_selection:4;	// [19:22]
		unsigned int rsvd3:1;	// [23]
		unsigned int flash_prot_key_read_out_flag:1;	// [24]
		unsigned int rsvd4:3;	// [25:27]
		unsigned int read_otp_key_sel:4;	// [31:28]
	} u;
};

enum HW_CHK_MODE {
	HW_CHK_DMA_MODE,
	HW_CHK_SC_MODE,
};

enum HW_CHK_INDEX_CTRL {
	HW_CHK_INDEX_CAN_DISABLE,
	HW_CHK_INDEX_CANNOT_DISABLE,
};

enum DMA_MODE
{
	PURE_DATA_MODE=0,//!< The operation data is raw/pure data. 
	TS_MODE=(1<<24),//!< The operation data is TS data. 
};

unsigned int dsc_get_data(void *base_addr, unsigned int offset);
void dma_src_addr_set(void *base_addr, dma_addr_t src);
void dma_transfer_length_set(void *base_addr,
		unsigned int length, enum DMA_MODE mode);
unsigned int get_dma_curr_write_addr(void *base_addr);
void dma_dma_scramble_ctrl_mode_select(void *base_addr, int mode);
void dma_dma_scramble_ctrl_select(void *base_addr, int sc);
void dma_dma_ts_format_select(void *base_addr, int ts_format);
void dma_dma_mode_select(void *base_addr, enum DMA_MODE mode);
void dma_data_target_select(void *base_addr,
			    enum DMA_DATA_TARGET target);
void dsc_dma_start(void *base_addr);
void dma_sync_byte_set(void *base_addr, unsigned char sync_byte);
unsigned int get_dma_interrupt_enable_status(void *base_addr);
void dma_interrupt_disable_all(void *base_addr);
void dma_interrupt_disable(void *base_addr, unsigned int int_flag);
void dma_interrupt_enable(void *base_addr, unsigned int int_flag);
unsigned char dma_get_dma_status(void *base_addr);
void dma_clear_dma_status(void *base_addr, unsigned int dma_status);


void dsc_target_addr_check_patch(void *base_addr, int crypto_mode);
void sha_mode_set(void *base_addr, enum SHA_MODE sha_mode);
void sha_data_source_select(void *base_addr, unsigned int sel);
void sha_flash_start(void *base_addr);
unsigned int sha_get_status(void *base_addr);
void sha_clear_status(void *base_addr);
void sha_flash_dma_addr_set(void *base_addr, unsigned int dma_addr);
void sha_flash_dma_length_set(void *base_addr, unsigned int length);
unsigned int sha_get_dma_status(void *base_addr);
unsigned int sha_get_digset_data(void *base_addr);
void sha_digest_select(void *base_addr, unsigned int sel);
void sha_endian_select(void *base_addr, unsigned int sel);
void sha_flash_data_endian(void *base_addr, unsigned int sel);
void sha_word_swap_select(void *base_addr, unsigned int sel);
void sha_set_scatter_mode(void *base_addr, unsigned char scatter_mode);
void sha_set_dma_stage(void *base_addr, unsigned char dma_stage);
void sha_set_total_len(void *base_addr, unsigned int total_len);
void sha_set_int_value(void *base_addr, unsigned char * iv);
void sha_get_int_value(void *base_addr, unsigned char * iv);
void sha_word_input_swap_select(unsigned int sel);
unsigned char sha_dma_get_dma_status(void *base_addr);
void sha_dma_clr_dma_status(void *base_addr);
void data_seq_set(void *base_address, enum DATA_SEQ data_seq);
void dsc_ip_reset(void *reset_register, unsigned char reset_bit);

#ifdef __cplusplus
}
#endif
#endif	/***/
