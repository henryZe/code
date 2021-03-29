#include "com_example_adcdisplay_NativeADC.h"

#include <android/log.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#define  LOG_TAG    "ADCTest"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define ADC_INPUT_PIN	_IOW('S', 0x0c, unsigned long)

int fd = -1;

jobject g_this;
JavaVM *g_jvm;

void * get_adc_main(void *arg) {

	JNIEnv *env;

	//在虚拟机中接合该线程,函数会赋值env变量
	(*g_jvm)->AttachCurrentThread(g_jvm, &env, NULL);

	jclass cls = (*env)->GetObjectClass(env, g_this);
	jmethodID methodId = (*env)->GetMethodID(env, cls, "getAdcDataListener",
			"(I)V");

	LOGI("%s", (char * )arg);

	for (;;) {
		int i;
		read(fd, &i, sizeof(int));

		(*env)->CallVoidMethod(env, g_this, methodId, i);

		usleep(500 * 1000);
	}

	//配合AttachCurrentThread使用
	(*g_jvm)->DetachCurrentThread(g_jvm);
	//配合NewGlobalRef使用
	(*env)->DeleteGlobalRef(env, g_this);
}

JNIEXPORT jint JNICALL Java_com_example_adcdisplay_NativeADC_openADCDev(
		JNIEnv *env, jobject object) {
	fd = open("/dev/adc", O_RDONLY);
	if (fd < 0) {
		perror("open ADC device:");
		return 1;
	}

	return 0;
}

JNIEXPORT void JNICALL Java_com_example_adcdisplay_NativeADC_startThread
(JNIEnv *env, jobject object)
{
//	ioctl(fd,ADC_INPUT_PIN,1);

	//赋值全局变量
	g_this = (*env)->NewGlobalRef(env, object);
	//获取jvm参数
	(*env)->GetJavaVM(env, &g_jvm);

	char *charac = "thread action!";

	pthread_t tid;
	//env以及jobject不可以通过创建线程简单传参(只能传递普通参数)
	pthread_create(&tid,NULL,get_adc_main,(void *)charac);
}

JNIEXPORT void JNICALL Java_com_example_adcdisplay_NativeADC_closeADCDev
(JNIEnv *env, jobject object)
{
	if (fd > 0)
	close(fd);
}
