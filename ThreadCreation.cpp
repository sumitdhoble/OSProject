#include<iostream>
#include<pthread.h>
#include"rdtsc.h"

#define CLOCK_RATE 3.4

using namespace std;

void doNothing();

int main(){
	int i,j,k;
	int iterations = 1000000, sum = 0 , avg = 0;
	long int startTime, endTime;
	float time;
	pthread_t thread;

	startTime = rdtsc();
	for(i = 0 ; i < iterations ; i++){
		pthread_create(&thread, NULL, (void *(*)(void *))doNothing, 0);
	}	
	endTime = rdtsc();
	time = (endTime	- startTime)/iterations*(1/CLOCK_RATE);
	cout << time << endl;
	return 0;
}

void doNothing(){
}
