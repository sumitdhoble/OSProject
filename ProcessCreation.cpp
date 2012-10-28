#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<sys/wait.h>
#include"rdtsc.h"

#define CLOCK_RATE 3.4

using namespace std;

int main(){
	int i,j,k;
	int iterations = 1, t = 0, pid = 0;
	
	long int startTime, endTime;

	startTime = rdtsc();
	pid = fork();
	endTime = rdtsc();
	if(pid != 0){
		t = (endTime - startTime)*(1/CLOCK_RATE);
		cout << t << endl;
		exit(0);
	}
	else {
		wait(NULL);
	}

	return 0;
}





