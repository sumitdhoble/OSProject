#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<cstdio>
#include<cstdlib>
#include"rdtsc.h"

#define FILE_NAME "SampleFile.txt"

#define FILE_LENGTH 1073741825

using namespace std;

int main(){

        int socket_desc = 0;

	long int startRTT, endRTT, startSetup, endSetup, startTearDown, endTearDown;
	long int RTT, setup, tearDown;

	startSetup = rdtsc();

        socket_desc = socket(AF_INET, SOCK_STREAM, 0);

        if(socket_desc == -1){
                cout << "Could not create socket" << endl;
        }

        struct sockaddr_in remote , local;

        remote.sin_addr.s_addr = htonl(INADDR_ANY);
        remote.sin_family = AF_INET;
        remote.sin_port = htons(11111);

        if( connect(socket_desc, (struct sockaddr *) &remote, sizeof(struct sockaddr_in) ) < 0 ){
                cout << "Could not connect to socket" << endl;
                return -1;
        }

	int i = -1;
        char *message, c;
	message = (char *)malloc(FILE_LENGTH*sizeof(char));
	FILE *fp = (FILE *)fopen(FILE_NAME, "r");

	
	do{
		i++;
		fscanf(fp, "%c",&message[i]);
	}while(message[i] != '\0');

        if( send(socket_desc, message, strlen(message), 0) < 0 ) {
                cout << "Send message failed" << endl;
                return -1;
        }

        close(socket_desc);

        return 0;
}

