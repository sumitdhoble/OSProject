#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

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

        char message[2];
	char message2[2] = {'w','\0'};

	if( recv(new_socket_desc, message, 2, 0) < 0 ) {
	      cout << "Recv message failed" << endl;
	      return -1;
	}else{
	   //   cout << "Message Received : " << message << endl;
	}

//	cout << "Sending message ... " << endl;

	if( send(new_socket_desc, message2, strlen(message2), 0) < 0 ){
		cout << "Could not send data to socket 2" << endl;
		return -1;
	}

        close(socket_desc);
  //      cout << "Server successful" << endl;
        return 0;
}

