#include "com_example_stepmotor_NativeOperate.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <android/log.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>

#define WON_MAGIC 'K'

#define clockwise 		_IO(WON_MAGIC,1)
#define anti_clockwise 	_IO(WON_MAGIC,2)
#define speedup 		_IO(WON_MAGIC,3)
#define speeddown 		_IO(WON_MAGIC,4)
#define exit_app 		_IO(WON_MAGIC,5)

#define  LOG_TAG    "SmotorTest"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

int fd = -1;

JNIEXPORT jint JNICALL Java_com_example_stepmotor_NativeOperate_openStepDev
  (JNIEnv *env, jobject object)
{
	fd = open("/dev/gec_smotor", O_RDWR);

	if (fd < 0) {
		LOGI("Can't open /dev/gec_smotor");
		return -1;
	}

	return 0;
}

JNIEXPORT jint JNICALL Java_com_example_stepmotor_NativeOperate_operateStep
  (JNIEnv *env, jobject object, jint num)
{
	int rnum;

	switch(num)
	{
		case 1:
			ioctl(fd,clockwise, 0);
			break;
		case 2:
			ioctl(fd,anti_clockwise, 0);
			break;
		case 3:
			ioctl(fd,speedup, 0);
			read(fd, &rnum, sizeof(rnum));
			return rnum;
			break;
		case 4:
			ioctl(fd,speeddown, 0);
			read(fd, &rnum, sizeof(rnum));
			return rnum;
			break;
		default:
			break;
	}

	return 0;
}

JNIEXPORT void JNICALL Java_com_example_stepmotor_NativeOperate_closeStepDev
  (JNIEnv *env, jobject object)
{
	if (fd > 0)
		close(fd);
}
