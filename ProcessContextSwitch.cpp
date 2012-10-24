#include<iostream>
#include<cstdlib>
#include<sys/time.h>
#include<unistd.h>
#include<sys/wait.h>
#include<cstdio>

using namespace std;

int main(){

	int i,j,k;
	int pid = 0, iterations = 100;
	char buf;
	int pipePC[2];
	int pipeCP[2];
	FILE *fp;

	 if (pipe(pipePC) == -1 || pipe(pipeCP) == -1) {
      exit(EXIT_FAILURE);
  }

	fp = (FILE *)fopen("ContextSwitch1StartTime.txt", "w");
	fp = (FILE *)fopen("ContextSwitch1EndTime.txt", "w");
	fp = (FILE *)fopen("ContextSwitch2StartTime.txt", "w");
	fp = (FILE *)fopen("ContextSwitch2EndTime.txt", "w");

	pid = fork();

	if(pid == 0){
		int i = iterations, t1 = 0;		
		struct timeval startTime, endTime, startTime2, endTime2;

		while(i > 0){
git			
			close(pipePC[1]);
			read(pipePC[0], &buf, 1);
			gettimeofday(&endTime, NULL);
			close(pipePC[0]);
			fp = (FILE *)fopen("ContextSwitch1EndTime.txt", "a");
			fprintf(fp,"%ld\t%ld\n", endTime.tv_sec, endTime.tv_usec);
			fclose(fp);

			close(pipeCP[0]);
			gettimeofday(&startTime2, NULL);
			write(pipeCP[1], "h" , 1);
			fp = (FILE *)fopen("ContextSwitch2StartTime.txt", "a");
			fprintf(fp,"%ld\t%ld\n", startTime2.tv_sec, startTime2.tv_usec);
			fclose(fp);

			close(pipeCP[1]);

			i--;
		}

		exit(0);
	}
	else {
		int i = iterations, t2 = 0;
		struct timeval startTime, endTime, startTime2, endTime2;

		while(i > 0){

			close(pipePC[0]);          
			gettimeofday(&startTime, NULL);
			write(pipePC[1], "w" , 1);
			fp = (FILE *)fopen("ContextSwitch1StartTime.txt", "a");
			fprintf(fp,"%ld\t%ld\n", startTime.tv_sec, startTime.tv_usec);
			fclose(fp);		  
			close(pipePC[1]);
			
			
			close(pipeCP[1]);
			read(pipeCP[0], &buf, 1);
			gettimeofday(&endTime2, NULL);
			fp = (FILE *)fopen("ContextSwitch2EndTime.txt", "a");
			fprintf(fp,"%ld\t%ld\n", endTime2.tv_sec, endTime2.tv_usec);
			fclose(fp);
			close(pipeCP[0]);

			i--;
		}

    wait(NULL);                /* Wait for child */
    exit(0);
	}

	return 0;
}





