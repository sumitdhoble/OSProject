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

	 if (pipe(pipePC) == -1 || pipe(pipeCP) == -1) {
      exit(EXIT_FAILURE);
  }

	pid = fork();
	
	if(pid == 0){
		int i = iterations, t1 = 0;
		FILE *fp;
		struct timeval startTime, endTime, startTime2, endTime2;

		while(i > 0){
			
			close(pipePC[1]);
			read(pipePC[0], &buf, 1);
			gettimeofday(&endTime, NULL);
			close(pipePC[0]);

			fp = (FILE *)fopen("fileParent.txt", "r");
			fscanf(fp,"%ld %ld", &startTime.tv_sec, &startTime.tv_usec);
			fclose(fp);
			t1 += (endTime.tv_sec - startTime.tv_sec)*1000000 + (endTime.tv_usec - startTime.tv_usec);

			close(pipeCP[0]);
			gettimeofday(&startTime2, NULL);
			fp = (FILE *)fopen("fileChild.txt", "w");
			fprintf(fp,"%ld %ld", startTime2.tv_sec, startTime2.tv_usec);
			fclose(fp);
			write(pipeCP[1], "h" , 1);
			close(pipeCP[1]);

			i--;
		}

		cout << "t1\t" << (float)t1 / iterations << endl;
		exit(0);
	}
	else {
		int i = iterations, t2 = 0;
		FILE *fp;
		struct timeval startTime, endTime, startTime2, endTime2;

		while(i > 0){

			close(pipePC[0]);          
			gettimeofday(&startTime, NULL);
			fp = (FILE *)fopen("fileParent.txt", "w");
			fprintf(fp,"%ld %ld", startTime.tv_sec, startTime.tv_usec);
			fclose(fp);
		  write(pipePC[1], "w" , 1);
			close(pipePC[1]);
			
			
			close(pipeCP[1]);
			read(pipeCP[0], &buf, 1);
			gettimeofday(&endTime2, NULL);
			fp = (FILE *)fopen("fileChild.txt", "r");
			fscanf(fp,"%ld %ld", &startTime2.tv_sec, &startTime2.tv_usec);
			fclose(fp);
			close(pipeCP[0]);
			t2 += (endTime2.tv_sec - startTime2.tv_sec)*1000000 + (endTime2.tv_usec - startTime2.tv_usec);

			i--;
		}

    wait(NULL);                /* Wait for child */
		cout << "t2\t" << (float)t2 / iterations << endl;
    exit(0);
	}

	return 0;
}





