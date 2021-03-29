#include <stdio.h>
#include "HelloWorld.h"

JNIEXPORT void JNICALL Java_HelloWorld_printContext(JNIEnv *env, jobject object)
{
	printf("Hello World\n");
};

