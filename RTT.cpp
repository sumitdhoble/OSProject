#include<iostream>
#include<cstdlib>
#include<sys/time.h>
#include<unistd.h>
#include<sys/wait.h>

using namespace std;

int main(){

	int i, iterations = 100, res1 = 0, res2 = 0 ;

	res1 = system("g++ server.cpp -o server");
	res2 = system("g++ client.cpp -o client");

	for( i = 0 ; i < iterations; i++){
		usleep(100);
		system("./server &");
		system("./client");
	}

}
