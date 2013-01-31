#include "myTest.h"

JNIEXPORT jstring JNICALL
	Java_com_example_neonbuild_MainActivity_doAllTheThings(JNIEnv* env, jobject thiz){
		
		struct timeval start, end;
		long stpElapsed, noStpElapsed, autoElapsed;
		long avgStpElapsed, avgNoStpElapsed, avgAutoElapsed;
		
		char rtStr[2048];
		//const int NUM_ELEM = 32768; //32kB is L1 cache (for Samsung Exynos 4412)
		const int NUM_ELEM = 2048;
		const int STP_SIZE = 4;
		const int AVG_PASS = 10;
		
		//do a little bit of simple float arithmetric (vector by scalar)
		float* src = malloc(sizeof(float)*NUM_ELEM); //eight floats
		float* dest = malloc(sizeof(float)*NUM_ELEM);
		
		//initialise the normal counters
		stpElapsed=0;
		noStpElapsed=0;
		autoElapsed=0;
		
		//initialise the average counters
		avgAutoElapsed=0;
		avgNoStpElapsed=0;
		avgStpElapsed=0;
		
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
			
			avgAutoElapsed+=autoElapsed;
			avgNoStpElapsed+=noStpElapsed;
			avgStpElapsed+=stpElapsed;
		}
		
		//average our runtimes
		avgAutoElapsed/=AVG_PASS;
		avgNoStpElapsed/=AVG_PASS;
		avgStpElapsed/=AVG_PASS;
		
		sprintf(rtStr, "Auto\t\t\tIt took %d \nNe10\tnostep:It took %d \n\t\tstep:It took %d microseconds \n",avgAutoElapsed,avgNoStpElapsed, avgStpElapsed);
		
		//free objects
		//free(src);
		//free(dest);
		
		return (*env)->NewStringUTF(env, rtStr);
}

JNIEXPORT jstring JNICALL
Java_com_example_neonbuild_MainActivity_stringFromJNI(JNIEnv* env, jobject thiz){
	
	return (*env)->NewStringUTF(env, "Hello from JNI! Please press the button to run some Ne10 and NEON tests");

}