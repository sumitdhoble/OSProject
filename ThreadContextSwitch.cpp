#include<iostream>
#include<pthread.h>
#include<sys/time.h>
#include<unistd.h>
#include<sched.h>
#include"rdtsc.h"

#define CLOCK_RATE 3.4

using namespace std;

void doNothing();
long int startTime, endTime;
int iterations = 1000000;
int i = 0;

int main(){
	int j,k;
	int sum = 0;
	float totalTime = 0.0, time = 0.0;	
	pthread_t thread;

	pthread_create(&thread, NULL, (void *(*)(void *))doNothing, NULL);
	startTime = rdtsc();
	for(i = 0 ; i < iterations ; i++){
		sched_yield();
	}
	endTime = rdtsc();
	pthread_join(thread, NULL);
	totalTime = (endTime - startTime) * (1/CLOCK_RATE);;
	time = (float)totalTime/(2*iterations);
	cout << time  << endl;
	return 0;
}

void doNothing(){
	while(i < iterations )
		sched_yield();	
}
