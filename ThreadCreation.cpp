#include<iostream>
#include<pthread.h>
#include<sys/time.h>
#include<unistd.h>

using namespace std;

void doNothing();

int main(){
	int i,j,k;
	int iterations = 1000000, sum = 0 , avg = 0, time = 0;
	struct timeval startTime, endTime;
	pthread_t thread;

	gettimeofday(&startTime, NULL);	
	for(i = 0 ; i < iterations ; i++){
		pthread_create(&thread, NULL, (void *(*)(void *))doNothing, 0);
	}	
	gettimeofday(&endTime, NULL);
	time = (endTime.tv_sec - startTime.tv_sec)*1000000 + (endTime.tv_usec - startTime.tv_usec);
	cout << time << endl;
	return 0;
}

void doNothing(){
}
