#include<iostream>
#include<cstdlib>
#include<sys/time.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){

	int i = 0, iterations = 100;

	system("g++ -pthread ThreadCreation.cpp -o ThreadCreation");

	for(i = 0; i < iterations; i++){
		usleep(1000);
		system("./ThreadCreation");
	}

	return 0;
}
