
#include "myTest.h"

JNIEXPORT jstring JNICALL
Java_com_example_neonbuild_MainActivity_stringFromJNI(JNIEnv* env, jobject thiz){
    
    //do a little bit of simple float arithmetric (vector by scalar)
    //if it runs, and computes the correct result... we know it works!
    
    float* src = malloc(sizeof(float)*1);
    src[0] = 1.5f;
    float* dest = malloc(sizeof(float)*1);
    addc_float_c(dest, src, 1.0f, 1);
    
    if (dest[0] == 2.5f) {
        return (*env)->NewStringUTF(env, "Hello from JNI! (ps... neon can compute floats too!)");
    }
    return (*env)->NewStringUTF(env, "Hello from JNI! (but... neon can't compute floats :( )");
}