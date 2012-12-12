#include"OSProject.h"
#include<sys/time.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string>
#include<sstream>

using namespace std;

int main(){

	string filesize, command1, command2, filename;
	char temp[50];
	long int size = 1024, increment = 1024*1024;

	int i = 0, iterations = 10;

	system("g++ CreateFile.cpp -o CreateFile");
	system("g++ FileCacheSize.cpp -o FileCacheSize");

	for(i = 0; i < iterations; i++){
		ostringstream stream1, stream2;
		stream1 << size;
		stream2 << i+1;
		filename = "SampleFile" + stream2.str() + ".txt";
		command1 = "./CreateFile " + filename + " " + stream1.str();
		system(command1.data());
		size += increment;
		command2 = "./FileCacheSize " + filename;
		system(command2.data());
	}

	cout << endl;

}
