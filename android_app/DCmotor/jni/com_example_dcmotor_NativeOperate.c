#include "com_example_dcmotor_NativeOperate.h"
#include <android/log.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>

#define WON_MAGIC 'K'
#define TURN_OFF  _IO(WON_MAGIC,0)
#define TURN_ON   _IO(WON_MAGIC,1)

#define  LOG_TAG    "DCmotorTest"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

int fd = -1;

struct data_t{
	int  direct;
};

JNIEXPORT jint JNICALL Java_com_example_dcmotor_NativeOperate_openDCmotorDev
  (JNIEnv *env, jobject object)
{
	fd = open("/dev/gec_DCmotor", O_RDWR);

	if (fd < 0) {
		LOGI("Can't open /dev/gec_DCmotor");
		return -1;
	}

	return 0;
}

JNIEXPORT void JNICALL Java_com_example_dcmotor_NativeOperate_operateDCmotor
  (JNIEnv *env, jobject object, jint turn, jint direct)
{
	struct data_t user_mode;
	switch(turn)
	{
		case 0:
			ioctl(fd, TURN_OFF, &user_mode);
			break;
		case 1:
			user_mode.direct = direct;
			ioctl(fd, TURN_ON, &user_mode);
			break;
		default:
			LOGI("invalid input");
			break;
	}
}

JNIEXPORT void JNICALL Java_com_example_dcmotor_NativeOperate_closeDCmotorDev
  (JNIEnv *env, jobject object)
{
	if (fd > 0)
		close(fd);
}
