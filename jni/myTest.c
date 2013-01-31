#include "myTest.h"

JNIEXPORT jstring JNICALL
	Java_com_example_neonbuild_MainActivity_doAllTheThings(JNIEnv* env, jobject thiz){
		
		struct timeval start, end;
		long stpElapsed, noStpElapsed, autoElapsed, neonElapsed;
		long avgStpElapsed, avgNoStpElapsed, avgAutoElapsed, avgNeonElapsed;
		
		char rtStr[2048];
		//const int NUM_ELEM = 32768; //32kB is L1 cache (for Samsung Exynos 4412)
		const int NUM_ELEM = 4096;
		const int STP_SIZE = 4;
		const int AVG_PASS = 1000;
		
		//do a little bit of simple float arithmetric (vector by scalar)
		float* src = malloc(sizeof(float)*NUM_ELEM); //eight floats
		float* dest = malloc(sizeof(float)*NUM_ELEM);
		
		//initialise the normal counters
		stpElapsed=0;
		noStpElapsed=0;
		autoElapsed=0;
		neonElapsed=0;
		
		//initialise the average counters
		avgAutoElapsed=0;
		avgNoStpElapsed=0;
		avgStpElapsed=0;
		avgNeonElapsed=0;
		
		for(int j = 0; j<AVG_PASS; j++){
			//set input array
			for(int i = 0; i < NUM_ELEM; i++){
				src[i] = i;
			}
			
			//time it as a whole (no stepping)
			gettimeofday(&start, NULL);
			for(int i = 0; i < NUM_ELEM; i ++){
				dest[i] = src[i]+1;
			}
			gettimeofday(&end, NULL);
			autoElapsed = (end.tv_sec-start.tv_sec)*1000000 + end.tv_usec-start.tv_usec;
			
			//reset input array
			for(int i = 0; i < NUM_ELEM; i++){
				src[i] = i;
			}
			
			//time it as a whole (no stepping)
			gettimeofday(&start, NULL);
			addc_float_c(dest,src,2.0f,NUM_ELEM);
			gettimeofday(&end, NULL);
			noStpElapsed = (end.tv_sec-start.tv_sec)*1000000 + end.tv_usec-start.tv_usec;
			
			
			//reset input array
			for(int i = 0; i < NUM_ELEM; i++){
				src[i] = i;
			}
			
			//time it stepping
			gettimeofday(&start, NULL);
			for(int i = 0; i < NUM_ELEM; i+=STP_SIZE){
				addc_float_c(dest+i+STP_SIZE, src+i+STP_SIZE, 2.0f, STP_SIZE);
			}
			gettimeofday(&end, NULL);
			stpElapsed = (end.tv_sec-start.tv_sec)*1000000 + end.tv_usec-start.tv_usec;
			
			//time it using neon
			gettimeofday(&start, NULL);
			for(int i = 0; i < NUM_ELEM; i+=4){
				float32x4_t src128 = vld1q_f32((const float32_t*)(src + i));
				float32x4_t tmp128 = vdupq_n_f32(2.0f);
				float32x4_t dst128 = vaddq_f32(src128,tmp128);
				vst1q_f32((float32_t*)(dest + i),dst128);
			}
			gettimeofday(&end, NULL);
			neonElapsed = (end.tv_sec-start.tv_sec)*1000000 + end.tv_usec-start.tv_usec;
			
			avgAutoElapsed+=autoElapsed;
			avgNoStpElapsed+=noStpElapsed;
			avgStpElapsed+=stpElapsed;
			avgNeonElapsed+=neonElapsed;
		}
		
		//average our runtimes
		avgAutoElapsed/=AVG_PASS;
		avgNoStpElapsed/=AVG_PASS;
		avgStpElapsed/=AVG_PASS;
		avgNeonElapsed/=AVG_PASS;
		
		//return the good news!
		sprintf(rtStr, "Auto\t\t\t\ttook %d \nNe10\tnostep:\ttook %d \n\t\t\tstep:\ttook %d\nNEON\t\t\t\ttook %d microseconds\n",avgAutoElapsed,avgNoStpElapsed, avgStpElapsed, avgNeonElapsed);
		return (*env)->NewStringUTF(env, rtStr);
}

JNIEXPORT jstring JNICALL
Java_com_example_neonbuild_MainActivity_stringFromJNI(JNIEnv* env, jobject thiz){
	
	return (*env)->NewStringUTF(env, "Hello from JNI! Please press the button to run some Ne10 and NEON tests");

}