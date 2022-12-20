#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "linkedlist.h"
#include "file.h"
#include "handle.h"



int main(int argc, char *argv[] ){

  if (argc != 2){
        printf("\nUsage: %s <Server Port>", argv[0]);
        return 0;
    }
  
  int sockfd, ret;
	struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

  int PORT = atoi(argv[1]);

	socklen_t addr_size;

	char buffer[1024];
  char buffer2[1024];
	pid_t childpid;

  int inputTime = 1;
  char server_mesg[256] = "Server connected successfully!\n";

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("Error in binding.\n");
		exit(1);
	}
	printf("Bind to port %d\n", PORT);

	if(listen(sockfd, 10) == 0){
		printf("Listening....\n");
	}else{
		printf("Error in binding.\n");
	}

  linkedList list;
  createSingleList(&list);
  readFileToList(&list);
  printSingleList(&list);

	while(1){
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		if(newSocket < 0){
			exit(1);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

		if((childpid = fork()) == 0){
			close(sockfd);

			do
   {
  //get username
    listen(sockfd, 5);
    read(newSocket, buffer, 1024);
    //printf("From client username: %s\n", buffer);
  //get password
    listen(sockfd, 5);
    read(newSocket, buffer2, 1024);
    //printf("From client password: %s\n", buffer2);
    
    if (sizeof(buffer) > 0 && sizeof(buffer2) > 0)
    {
      if (getUserAndPass(&list, buffer,buffer2) ==1 )
      {
        strcpy(server_mesg, "User signed in!\n");
        send(newSocket, server_mesg, sizeof(server_mesg), 0);
        exit(1);
        
      }
      else if (getUserAndPass(&list, buffer,buffer2) ==0)
      {
        strcpy(server_mesg, "Account not ready\n");
        send(newSocket, server_mesg, sizeof(server_mesg), 0);
      }
      
      else
      {
        strcpy(server_mesg, "Username is incorrect, please try again\n");
        send(newSocket, server_mesg, sizeof(server_mesg), 0);
        inputTime++;
      }
    }
    if (inputTime == 3)
  {
    strcpy(server_mesg, "Wrong username or password 3 times\n");
    send(newSocket, server_mesg, sizeof(server_mesg), 0);
   }
  }
   while (inputTime<4);
		}
}
	

	close(newSocket);


	return 0;
}