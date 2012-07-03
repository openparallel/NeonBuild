
#include "myTest.h"

JNIEXPORT jstring JNICALL
Java_com_example_neonbuild_MainActivity_stringFromJNI(JNIEnv* env, jobject thiz){
    
    return (*env)->NewStringUTF(env, "Hello from JNI !");
}