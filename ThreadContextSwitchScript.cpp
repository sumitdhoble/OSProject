#include<iostream>
#include<cstdlib>
#include<sys/time.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){

	int i = 0, iterations = 100;

	system("g++ -pthread ThreadContextSwitch.cpp -o ThreadContextSwitch");

	for(i = 0; i < iterations; i++){
		system("./ThreadContextSwitch");
		usleep(100);
	}

	return 0;
}
