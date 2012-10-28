#include<iostream>
#include<cstdlib>
#include<unistd.h>
#include<sys/wait.h>
#include<cstdio>
#include"rdtsc.h"

#define CLOCK_RATE 3.4

using namespace std;

int main(){

	int i,j,k;
	int pid = 0, iterations = 1000000;
	int pipePC[2];
	int pipeCP[2];
	FILE *fp;

	if (pipe(pipePC) == -1 || pipe(pipeCP) == -1) {
      		exit(EXIT_FAILURE);
	}

	pid = fork();

	if(pid == 0){
		int i = iterations, t1 = 0, time1;		
		long int startTime1, endTime1, startTime2, endTime2;
		char buf;

		startTime1 = rdtsc();
		for(i = iterations; i > 0; i--){
			
			close(pipePC[1]);
			read(pipePC[0], &buf, 1);
			close(pipePC[0]);
			//cout << "Received " << buf << endl; 

			close(pipeCP[0]);
			write(pipeCP[1], "h" , 1);
			close(pipeCP[1]);
			//cout << "Written " << "h" << endl;
		}
		endTime1 = rdtsc();
		time1 = (endTime1 - startTime1) * (1 / CLOCK_RATE);
		cout << (float)time1/(iterations) << endl;

		exit(0);
	}
	else {
		int i = iterations, t2 = 0, time2;
		long int startTime1, endTime1, startTime2, endTime2;
		char buf;
	
		startTime2 = rdtsc();
		for(i = iterations; i > 0; i--){

			close(pipePC[0]);          
			write(pipePC[1], "w" , 1);
			close(pipePC[1]);
			//cout << "Written w" << endl;
			
			
			close(pipeCP[1]);
			read(pipeCP[0], &buf, 1);
			close(pipeCP[0]);
			//cout << "Received "  << buf << endl;
		}
		endTime2 = rdtsc();
		time2 = (endTime2 - startTime2) * ( 1 / CLOCK_RATE );
		cout <<  (float)time2/(iterations) << endl;


		    wait(NULL);               /* Wait for child */
		    exit(0);
	}

	return 0;
}





