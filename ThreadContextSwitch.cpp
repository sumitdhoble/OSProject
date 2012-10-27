#include<iostream>
#include<pthread.h>
#include<sys/time.h>
#include<unistd.h>
#include<sched.h>
using namespace std;

void doNothing();
struct timeval startTime, endTime;
int iterations = 10000;
int i = 0;

int main(){
	int j,k;
	int sum = 0, time = 0;
	float avg = 0;	
	pthread_t thread;

	pthread_create(&thread, NULL, (void *(*)(void *))doNothing, NULL);
	gettimeofday(&startTime, NULL);	
	for(i = 0 ; i < iterations ; i++){
		sched_yield();
	}
	gettimeofday(&endTime, NULL);
	time = (endTime.tv_sec - startTime.tv_sec)*1000000 + (endTime.tv_usec - startTime.tv_usec);
	cout << time << endl;
	sum += time;
	pthread_join(thread, NULL);
	avg = (float)sum/(2*iterations);
	cout << "Average : " << avg << endl;
	return 0;
}

void doNothing(){
	while(i < iterations )
		sched_yield();	
}
