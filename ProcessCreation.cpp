#include<iostream>
#include<cstdlib>
#include<sys/time.h>
#include<unistd.h>

using namespace std;

int main(){
	int i,j,k;
	int iterations = 100, sum = 0 , avg = 0, time = 0;
	struct timeval startTime, endTime;
	pthread_t thread;

	for(i = 0 ; i < iterations ; i++){
		gettimeofday(&startTime, NULL);	
		system("./SampleTask.out &");
		gettimeofday(&endTime, NULL);
		time = (endTime.tv_sec - startTime.tv_sec)*1000000 + (endTime.tv_usec - startTime.tv_usec);
		cout << time << endl;
		sum += time;
	}	

	avg = sum/iterations;
	cout << "Average : " << avg << endl;
	return 0;
}





