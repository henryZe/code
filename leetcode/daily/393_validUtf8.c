#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int count_len(int data)
{
	if (data < 0x80) {
		return 1;
	} else if (0xc0 <= data && data < 0xe0) {
		return 2;
	} else if (0xe0 <= data && data < 0xf0) {
		return 3;
	} else if (0xf0 <= data && data < 0xf8) {
		return 4;
	}

	return -1;
}

int judge_valid(int *data, int dataSize)
{
	int len = count_len(data[0]);
	if (len < 0)
		return -1;

	if (len > dataSize)
		return -1;

	for (int i = 1; i < len; i++) {
		if ((data[i] & 0xC0) != 0x80)
			return -1;
	}

	return len;
}

bool validUtf8(int* data, int dataSize)
{
	int *end_data = data + dataSize;
	int len;

	while (data != end_data) {
		len = judge_valid(data, dataSize);
		if (len < 0)
			return false;

		data += len;
		dataSize -= len;
	}

	return true;
}
