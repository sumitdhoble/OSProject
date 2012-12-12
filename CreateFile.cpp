#include<iostream>
#include<cstdio>
#include<cstdlib>

int main(){

	long int filesize = 1073741824, i = 0;
	FILE *fp = fopen("SampleFile.txt","w");
	char c = 'a';
	int k;

	while( i < filesize){
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
}
