#include <stdio.h>
#include "HelloWorld.h"

JNIEXPORT jstring JNICALL Java_HelloWorld_printContext(JNIEnv *env, jobject object, jstring Str)
{
	const char* print = (*env)->GetStringUTFChars(env, Str, 0);
	printf("%s\n", print);

	const char* cstring = "return from C";
	jstring return_val = (*env)->NewStringUTF(env, cstring);
	return return_val;
};

