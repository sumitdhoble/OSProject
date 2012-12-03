#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

using namespace std;

int main(){

        int socket_desc = 0;
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

        char message[2] = "h";
        if( send(socket_desc, message, strlen(message), 0) < 0 ) {
                cout << "Send message failed" << endl;
                return -1;
        }

        if( recv(socket_desc, message, 100, 0 ) < 0 ) {
               cout << "Receiving messsage failed" << endl;
                return -1;
        }

        close(socket_desc);

        return 0;
}

