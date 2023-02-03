
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: 上机编程认证
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除
 */
#include <stdio.h>
#include <string.h>

#define MAX_OUTPUT_LEN 13

static int most_significant_bit(unsigned int unicodeVal)
{
	int i, ret;

	for (i = 31; i > 0; i--) {
		ret = unicodeVal & (1 << i);
		if (ret != 0) {
			break;
		}
	}
	return i;
}

static void loop_encode(int most_sig, int highest, unsigned int unicodeVal, char outBuf[])
{
	unsigned char valid;
	char tmp[10];

	if (most_sig >= highest) {
		valid = unicodeVal & 0b111111;
		valid |= (1 << 6);

		loop_encode(most_sig - 6, highest - 1, unicodeVal >> 6, outBuf);
		sprintf(tmp, "%02X", valid);
		strcat(outBuf, tmp);
		return;
	}

	valid = unicodeVal | (1 << highest);
	sprintf(tmp, "%02X", valid);
	strcat(outBuf, tmp);
	return;
}

// 待实现函数，在此函数中填入答题代码
// 生成的信息列表存于outBuf中，outBufLen是最大数组长度
static void XutfEncoding(unsigned int unicodeVal, char outBuf[], int outBufLen)
{
	int msig;
	unsigned int valid;

	msig = most_significant_bit(unicodeVal);
	if (msig < 7) {
		valid = unicodeVal | (1 << 7);
		sprintf(outBuf, "%X", valid);
		return;
	}

	loop_encode(msig, 6, unicodeVal, outBuf);
}

int main(void)
{
    unsigned int unicodeVal;
    if (scanf("%u", &unicodeVal) != 1) { return -1; }

    char outBuf[MAX_OUTPUT_LEN] = { 0 };
    XutfEncoding(unicodeVal, outBuf, MAX_OUTPUT_LEN);

    printf("%s", outBuf);

    return 0;
}
