
#ifdef ANDROID

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <jni.h>
#include <android/log.h>
#include <sys/time.h>
#include <time.h>

//Ne10 libraries
#include "inc/NE10_c.h"
#include "inc/NE10_types.h"

//also use the Neon framework
#include <arm_neon.h>

#define LOGV(...) __android_log_print(ANDROID_LOG_SILENT, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

	JNIEXPORT jstring JNICALL
		Java_com_example_neonbuild_MainActivity_stringFromJNI(JNIEnv* env, jobject thiz);
	
	
	JNIEXPORT jstring JNICALL
		Java_com_example_neonbuild_MainActivity_doAllTheThings(JNIEnv* env, jobject thiz);
	
	
#endif