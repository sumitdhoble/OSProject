#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<cstdlib>
#include"rdtsc.h"

#define FILE_LENGTH 1073741825
#define CLOCK_RATE 3.4

using namespace std;

int main(){

        int socket_desc = 0, new_socket_desc;
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);

        if(socket_desc < 0){
                cout << "Could not create socket" << endl;
        }

        struct sockaddr_in remote , local;

        remote.sin_addr.s_addr = htonl(INADDR_ANY);
        remote.sin_family = AF_INET;
        remote.sin_port = htons(11111);

        socklen_t len = sizeof(remote);
        new_socket_desc = bind(socket_desc, (struct sockaddr *) &remote, len);
        if( new_socket_desc < 0){
                cout << "Bind Failed " << new_socket_desc << endl;
                return -1;
        }

        new_socket_desc = listen(socket_desc, 5);
        if( new_socket_desc  < 0 ){
                cout << "Listen failed " << new_socket_desc << endl;
                return -1;
        }
                                                                                                                                                                    
        new_socket_desc = accept(socket_desc, (struct sockaddr *) &remote, &len );
        if( new_socket_desc < 0){
               cout << "Error accepting connection to socket" << endl;
                return -1;
        }

        char *message;
	long int startTime = 0, endTime = 0, time = 0;
	double bandwidth = 0.0;

	message = (char*)malloc(sizeof(char)*FILE_LENGTH); 

	startTime = rdtsc();
	long int bytes = 0;

	while(bytes < FILE_LENGTH - 1){
		bytes += recv(new_socket_desc, message, FILE_LENGTH,  0);	
		if( bytes < 0 ) {
			cout << "Recv message failed" << endl;
			return -1;
		}else{
			cout << bytes << endl;
		}
	}

	endTime  = rdtsc();
	time = (endTime - startTime)* (1/CLOCK_RATE);
	bandwidth = bytes*1000.0/time;

	cout << "Bytes read : " << bytes << endl; 
	cout << "Time require : " << time << endl;
	cout << "Bandwidth recorded : " << bandwidth << " KBps " << endl;

	close(socket_desc);
	close(new_socket_desc);

        return 0;
}

