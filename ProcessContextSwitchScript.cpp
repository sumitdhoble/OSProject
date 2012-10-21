#include<iostream>
#include<cstdlib>
#include<sys/time.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){

	int i = 0, iterations = 20;

	system("g++ ProcessContextSwitch.cpp -o ProcessContextSwitch");

	for(i = 0; i < iterations; i++){
		system("./ProcessContextSwitch");
		sleep(1);
	}

	return 0;
}
