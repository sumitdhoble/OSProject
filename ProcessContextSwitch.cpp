#include<iostream>
#include<cstdlib>
#include<sys/time.h>
#include<unistd.h>
#include<sys/wait.h>
#include<cstdio>

using namespace std;




int main(){

	int i,j,k;
	int pid = 0, iterations = 1;
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
			
			cout << "receiving" << endl;
			close(pipePC[1]);
			while (read(pipePC[0], &buf, 1) < 0);
			gettimeofday(&endTime, NULL);
			close(pipePC[0]);
			cout << "received" << endl;
			fp = (FILE *)fopen("fileParent.txt", "r");
			fscanf(fp,"%ld %ld", &startTime.tv_sec, &startTime.tv_usec);
			fclose(fp);
			cout << "Start Time Read in Child fileParent.txt " << startTime.tv_sec << " " << startTime.tv_usec << endl;
			t1 += (endTime.tv_sec - startTime.tv_sec)*1000000 + (endTime.tv_usec - startTime.tv_usec);
			//cout << t1 << endl;


			close(pipeCP[0]);
			gettimeofday(&startTime2, NULL);
			cout << "Start Time Written in Child fileChild.txt " << startTime2.tv_sec << " " << startTime2.tv_usec << endl;
			fp = (FILE *)fopen("fileChild.txt", "w");
			fprintf(fp,"%ld %ld", startTime2.tv_sec, startTime2.tv_usec);
			fclose(fp);
			write(pipeCP[1], "h" , 1);
			close(pipeCP[1]);

			i--;
		}

		cout << "t1 : " << (float)t1 / iterations << endl;
		exit(0);
	}
	else {
		int i = iterations, t2 = 0;
		FILE *fp;
		struct timeval startTime, endTime, startTime2, endTime2;

		while(i > 0){
			close(pipePC[1]);          
			gettimeofday(&startTime, NULL);
			fp = (FILE *)fopen("fileParent.txt", "w");
			fprintf(fp,"%ld %ld", startTime.tv_sec, startTime.tv_usec);
			fclose(fp);
		  write(pipePC[0], "w" , 1);
			close(pipePC[0]);
			cout << "sending Start Written in Parent PC fileParent.txt: " << startTime.tv_sec << " " << startTime.tv_usec << endl;
			cout << "sent" << endl; 
			
			
			close(pipeCP[1]);
			while( read(pipeCP[0], &buf, 1) < 0);
			gettimeofday(&endTime2, NULL);
			fp = (FILE *)fopen("fileChild.txt", "r");
			fscanf(fp,"%ld %ld", &startTime2.tv_sec, &startTime2.tv_usec);
			fclose(fp);
			close(pipeCP[0]);
			cout << "Start Time Read in Parent fileChild.txt " << startTime2.tv_sec << " " << startTime2.tv_usec << endl;
			t2 += (endTime2.tv_sec - startTime2.tv_sec)*1000000 + (endTime2.tv_usec - startTime2.tv_usec);

			i--;			
		}

    wait(NULL);                /* Wait for child */
		cout << "t2 : " << (float)t2 / iterations << endl;
    exit(0);
	}

	return 0;
}





