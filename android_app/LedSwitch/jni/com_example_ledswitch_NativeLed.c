#include "com_example_ledswitch_NativeLed.h"
#include <android/log.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>

#define IOCTL_LED_ON    0
#define IOCTL_LED_OFF   1

#define  LOG_TAG    "LedTest"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define LED_MAGIC 'x'                       //设置IOCTL的魔数
#define LED1 _IO(LED_MAGIC,0)
#define LED2 _IO(LED_MAGIC,1)
#define LED3 _IO(LED_MAGIC,2)
#define LED4 _IO(LED_MAGIC,3)
#define MAX_NR 4

int fd = -1;

JNIEXPORT jint JNICALL Java_com_example_ledswitch_NativeLed_openLedDev(
		JNIEnv *env, jobject object) {
	fd = open("/dev/leds", O_RDWR);  // 打开设备

	if (fd < 0) {
		LOGI("Can't open /dev/leds\n");
		return -1;
	}

	return 0;
}

JNIEXPORT void JNICALL Java_com_example_ledswitch_NativeLed_operateLed(JNIEnv *env, jobject object, jint led_pos, jstring operate)
{
	int led_no = led_pos-1;

	const char *coperate = (*env)->GetStringUTFChars(env, operate, 0);

	if (!strcmp(coperate, "on")) {           //开灯
		switch(led_no)
		{
			case 0:
			ioctl(fd,LED1,IOCTL_LED_ON);
			break;

			case 1:
			ioctl(fd,LED2,IOCTL_LED_ON);
			break;

			case 2:
			ioctl(fd,LED3,IOCTL_LED_ON);
			break;

			case 3:
			ioctl(fd,LED4,IOCTL_LED_ON);
			break;

			default:
			break;
		}
	} else if (!strcmp(coperate, "off")) {           //关灯

		switch(led_no)
		{
			case 0:
			ioctl(fd,LED1,IOCTL_LED_OFF);
			break;

			case 1:
			ioctl(fd,LED2,IOCTL_LED_OFF);
			break;

			case 2:
			ioctl(fd,LED3,IOCTL_LED_OFF);
			break;

			case 3:
			ioctl(fd,LED4,IOCTL_LED_OFF);
			break;

			default:
			break;
		}
	}
}

JNIEXPORT void JNICALL Java_com_example_ledswitch_NativeLed_closeLedDev(JNIEnv *env, jobject object)
{
	if (fd > 0)
	close(fd);
}
