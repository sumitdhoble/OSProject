#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include"rdtsc.h"

#define CLOCK_RATE 3.4

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

	endSetup = rdtsc();

	startRTT = rdtsc();

        char message[2] = { 'h', '\0' };
        if( send(socket_desc, message, strlen(message), 0) < 0 ) {
                cout << "Send message failed" << endl;
                return -1;
        }

        if( recv(socket_desc, message, 100, 0 ) < 0 ) {
               cout << "Receiving messsage failed" << endl;
                return -1;
        }

	endRTT = rdtsc();

	startTearDown = rdtsc();

        close(socket_desc);

	endTearDown = rdtsc();

	setup = (endSetup - startSetup)*(1/CLOCK_RATE);
	RTT = (endRTT - startRTT) * (1/CLOCK_RATE);
	tearDown = (endTearDown - startTearDown)*(1/CLOCK_RATE);

	cout << setup << "\t" << RTT << "\t" << tearDown << endl;

        return 0;
}

