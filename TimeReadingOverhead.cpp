#include<iostream>
#include"rdtsc.h"

#define CLOCK_RATE 3.4

using namespace std;

int main(){
	int i, j, k, l, m, n, o, p;
	bool comparison;
	int iterations = 1000000;
	int measurements = 100;
//	struct timeval startTime, endTime, testTime, testTime2, testTime3;
	int runtime;
	float measurementResult = 0.0, finalResult = 0.0, sum = 0.0;
	long int startTime, endTime;

	for (i = 0; i < measurements; i++) {
		startTime = rdtsc();
		for (j = 0; j < iterations; j++) {
			rdtsc();
			rdtsc();
			rdtsc();
		}
		endTime = rdtsc();
		runtime = endTime - startTime;
		measurementResult = (float)runtime/iterations*(1/CLOCK_RATE);
		cout << measurementResult << endl;
	}
	//finalResult = (float)sum/measurements;
	//cout << finalResult << endl;
	
	return 0;
}
