#include <stdio.h>
#include "HelloWorld.h"

JNIEXPORT jstring JNICALL Java_HelloWorld_printContext(JNIEnv *env, jobject object, jstring Str)
{
	const char* print = (*env)->GetStringUTFChars(env, Str, 0);
	printf("%s\n", print);

	//获得成员值
	//找到指定的类
	jclass targetClass = (*env)->FindClass(env, "HelloWorld");
	//找到类的成员标签
	jfieldID targetID = (*env)->GetFieldID(env, targetClass, "a", "I");
	//得到对应成员值
	jint a = (*env)->GetIntField(env, object, targetID);

	printf("HelloWorld.a = %d\n",a);

	//调用类方法
	//方法标签
	//Object method
	jmethodID methodId = (*env)->GetMethodID(env, targetClass, "JavaPrint", "()V");
	(*env)->CallVoidMethod(env, object, methodId);
		
	//static method
	jmethodID staticId = (*env)->GetStaticMethodID(env, targetClass, "JavaSystem", "()V");
	(*env)->CallStaticVoidMethod(env, targetClass, staticId);

	const char* cstring = "return from C";
	jstring return_val = (*env)->NewStringUTF(env, cstring);
	return return_val;
};
