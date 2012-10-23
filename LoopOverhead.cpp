#include<iostream>
#include<pthread.h>
#include<sys/time.h>
#include<unistd.h>

using namespace std;

void doNothing(int i, int j, int k, int l, int m, int n, int o, int p){
}


int main(){
	int i, j, k, l, m, n, o, p;
	bool comparison;
	int iterations = 100000000;
	int measurements = 100;
	struct timeval startTime, endTime, testTime;
	int runtime, sum = 0;

	for (i = 0; i < measurements; i++) {
		gettimeofday(&startTime, NULL);
		for (j = 0; j < iterations; j++) {
			//gettimeofday(&testTime, NULL);
			doNothing(i, j, k, l, m, n, o, p);
		}
		gettimeofday(&endTime, NULL);
		runtime = (endTime.tv_sec - startTime.tv_sec)*1000000 + (endTime.tv_usec - startTime.tv_usec);
		cout << runtime << endl;
		sum += runtime;
	}
	cout << sum/measurements << endl;
	sum = 0;
}
