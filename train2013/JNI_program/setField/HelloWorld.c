#include <stdio.h>
#include "HelloWorld.h"

struct device_data 
{
	char *name;
	char *data;
};

JNIEXPORT jobject JNICALL Java_HelloWorld_createPerson(JNIEnv *env, jobject object, jint age, jstring name)
{
	//目标创建类
	jclass personClass = (*env)->FindClass(env, "Person");
	//构造器ID
	jmethodID createID = (*env)->GetMethodID(env, personClass, "<init>", "()V");
	jobject person = (*env)->NewObject(env, personClass, createID);

	
	//对创建对象进行赋值
	jfieldID ageID = (*env)->GetFieldID(env, personClass, "age", "I");
	(*env)->SetIntField(env, person, ageID, age);

	jfieldID nameID = (*env)->GetFieldID(env, personClass, "name", "Ljava/lang/String;");
	(*env)->SetObjectField(env, person, nameID, name);
	
	struct device_data exam = (struct device_data)malloc(sizeof(struct device_data));
	exam.name = "DC_motor";
	exam.data = "100km/h";

	
	
	return person;
};
