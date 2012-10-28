#include<iostream>
#include<cstdlib>
#include<sys/time.h>
#include<unistd.h>
#include<sys/wait.h>
#include<cstdio>

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
		struct timeval startTime1, endTime1, startTime2, endTime2;
		char buf;

		gettimeofday(&startTime1, NULL);
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
		gettimeofday(&endTime1, NULL);
		time1 = (endTime1.tv_sec - startTime1.tv_sec)*1000000 + (endTime1.tv_usec - startTime1.tv_usec);
		cout << (float)time1/(iterations) << endl;

		exit(0);
	}
	else {
		int i = iterations, t2 = 0, time2;
		struct timeval startTime1, endTime1, startTime2, endTime2;
		char buf;

		gettimeofday(&startTime2, NULL);
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
		gettimeofday(&endTime2, NULL);
		time2 = (endTime2.tv_sec - startTime2.tv_sec)*1000000 + (endTime2.tv_usec - startTime2.tv_usec);
		cout <<  (float)time2/(iterations) << endl;


		    wait(NULL);               /* Wait for child */
		    exit(0);
	}

	return 0;
}





