#include<iostream>
#include"OSProject.h"

using namespace std;

int main(int argc, char *argv[]){

	FILE *fp;
	char c;
	long int start, end, time, filesize = 0;

	if(argc < 2){
		cout << "Insufficient number of arguments" << endl;
		return -1;
	}
	
	fp = fopen(argv[1], "r");

	start = rdtsc();
	do{
		fscanf(fp,"%c",&c);
		filesize++;
	}while(c != '\0');
	end = rdtsc();

	time = (end - start)*(1/CLOCK_RATE);
	cout << filesize << "\t\t\t" << time << endl;	
}
