#include<iostream>
#include<cstdlib>
#include<sys/time.h>
#include<unistd.h>
#include<sys/wait.h>

using namespace std;

int main(){
	int i,j,k;
	int iterations = 1, t = 0, pid = 0;
	
	struct timeval startTime, endTime;

	gettimeofday(&startTime, NULL);	
	pid = fork();
	gettimeofday(&endTime, NULL);
	if(pid == 0){
		t= (endTime.tv_sec - startTime.tv_sec)*1000000 + (endTime.tv_usec - startTime.tv_usec);
		cout << t << endl;
		exit(0);
	}
	else {
		wait(NULL);
	}

	return 0;
}





