#include<iostream>
#include<cstdlib>
#include<sys/time.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){

	int i = 0, iterations = 100000;

	system("g++ ProcessCreation.cpp -o ProcessCreation");

	for(i = 0; i < iterations; i++){
		usleep(1000);
		system("./ProcessCreation");
	}

	return 0;
}
