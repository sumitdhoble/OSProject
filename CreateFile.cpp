#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;

int main(int argc, char *argv[]){

	if(argc < 3){
		cout << "Insufficient number of arguments" << endl;
		return -1;
	}

	char *filename = argv[1];
	int i = 0;
	long int filesize = atoi(argv[2]);

	FILE *fp = fopen(filename,"w");
	char c = 'a';
	int k;

	while( i < filesize ){
		fprintf(fp, "%c", c);
		if(c == 'z')
			c = 'a';
		else{
			k = (int)c;
			c = (char)(++k);
		}
		i++;
	}

	c = '\0';
	fprintf(fp, "%c", c);

	fclose(fp);

	return 0;
}
