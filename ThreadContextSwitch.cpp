#include<iostream>
#include<pthread.h>
#include<sys/time.h>
#include<unistd.h>

using namespace std;

void doNothing(struct timeval *time);

struct timeval startTime, endTime;

int main(){
	int i,j,k;
	int iterations = 10000, sum = 0 , avg = 0, time = 0;	
	pthread_t thread;

	for(i = 0 ; i < iterations ; i++){
		gettimeofday(&startTime, NULL);
		pthread_create(&thread, NULL, (void *(*)(void *))doNothing, &endTime);
		pthread_join(thread, NULL);
		time = (endTime.tv_sec - startTime.tv_sec)*1000000 + (endTime.tv_usec - startTime.tv_usec);
		cout << time << endl;
		sum += time;
	}

	avg = sum/iterations;
	cout << "Average : " << avg << endl;
	return 0;
}

void doNothing(struct timeval *time){
	gettimeofday(time, NULL);	
}