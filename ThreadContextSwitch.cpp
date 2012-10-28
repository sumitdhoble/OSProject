#include<iostream>
#include<pthread.h>
#include<sys/time.h>
#include<unistd.h>
#include<sched.h>
using namespace std;

void doNothing();
struct timeval startTime, endTime;
int iterations = 1000000;
int i = 0;

int main(){
	int j,k;
	int sum = 0, totalTime = 0;
	float time = 0;	
	pthread_t thread;

	pthread_create(&thread, NULL, (void *(*)(void *))doNothing, NULL);
	gettimeofday(&startTime, NULL);	
	for(i = 0 ; i < iterations ; i++){
		sched_yield();
	}
	gettimeofday(&endTime, NULL);
	pthread_join(thread, NULL);
	totalTime = (endTime.tv_sec - startTime.tv_sec)*1000000 + (endTime.tv_usec - startTime.tv_usec);
	time = (float)totalTime/(2*iterations);
	cout << time  << endl;
	return 0;
}

void doNothing(){
	while(i < iterations )
		sched_yield();	
}
