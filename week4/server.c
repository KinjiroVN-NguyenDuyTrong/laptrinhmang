#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "file.h"
#include "handle.h"



int main(int argc, char *argv[] ){

  if (argc != 2){
        printf("\nUsage: %s <Server Port>", argv[0]);
        return 0;
    }
  
    struct sockaddr_in server, client_send, client_receive;
    int server_sock;
    char buffer[1024];
    char buffer2[1024];
    int bytes_sent, bytes_received, sin_size;
    int port = atoi(argv[1]);
    int inputTime = 1;
    char server_mesg[256] = "Server connected successfully!\n";
  

  /* :Construct a UDP socket
        -Make IPv4 Internet protocols.
        -Supports datagrams (data truyền theo từng gói một).
        -Only a single protocol exists to support a particular 
        socket type within a given protocol family.
  */
  server_sock=socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock == -1){
        // Call socket() to create a socket
        perror("\nError: ");
        return 0;
  }

  //Define the address of the server
    
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = INADDR_ANY;
  
  bind(server_sock, (struct sockaddr *)&server, sizeof(server));
  printf("\nServer is running on port %d\n",port);

  listen(server_sock, 5);
  linkedList list;
  createSingleList(&list);
  readFileToList(&list);
  printSingleList(&list);
  int client_socket;
  client_socket = accept(server_sock, NULL, NULL);
  send(client_socket, server_mesg, sizeof(server_mesg), 0);
   
   do
   {
  //get username
    listen(server_sock, 5);
    read(client_socket, buffer, 1024);
    //printf("From client username: %s\n", buffer);
  //get password
    listen(server_sock, 5);
    read(client_socket, buffer2, 1024);
    //printf("From client password: %s\n", buffer2);
    if (sizeof(buffer) > 0 && sizeof(buffer2) > 0)
    {
      if (userAuth(&list, buffer,buffer2) != NULL)
      {
        strcpy(server_mesg, "User signed in!\n");
        send(client_socket, server_mesg, sizeof(server_mesg), 0);
        listen(server_sock, 5);
        read(client_socket, buffer, 1024);
        if(strcmp(buffer,"bye")==0){
        strcpy(server_mesg, "Goodbye!\n");
        send(client_socket, server_mesg, sizeof(server_mesg), 0);
        return 0;
        }
      }
      else
      {
        strcpy(server_mesg, "Username is incorrect, please try again\n");
        send(client_socket, server_mesg, sizeof(server_mesg), 0);
        inputTime++;
      }
    }
    if (inputTime == 3)
  {
    strcpy(server_mesg, "Wrong username or password 3 times\n");
    send(client_socket, server_mesg, sizeof(server_mesg), 0);
   }
  }
   while (inputTime<4);
   
  return 0;
}