#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#define BUFF_SIZE 1024
int main(int argc, char *argv[])
{
  if (argc != 3){
        printf("Usage: %s <Server IP> <Server Port>\n", argv[0]);
        return 0;
    }
    int client_sock;
    struct sockaddr_in server_addr;
    char buff[BUFF_SIZE];
    char server_response[256],username[30],message[1024],password[30];
    int time = 0;
  int status = 0;

    char SERV_IP[16];
    int SERV_PORT;


    strcpy(SERV_IP, argv[1]);
    SERV_PORT = atoi(argv[2]);

    // Step 1: Construct a UDP socket
    if((client_sock=socket(AF_INET, SOCK_STREAM, 0)) < 0){
        // Call socket() to create a socket
        perror("\nError: ");
        return 0;
    }

    // Step 2: Define the address of the server
    //bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERV_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERV_IP); // converse ip adderss from string to network ip (int)
    printf("Server IP: %s - Port: %d\n", SERV_IP, SERV_PORT);
  
  // Convert IPv4 and IPv6 addresses from text to binary form
  if (inet_pton(AF_INET, SERV_IP, &server_addr.sin_addr) <= 0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

  if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}

  recv(client_sock, &server_response, sizeof(server_response), 0);
  
  printf("Tu server: %s\n", server_response);
    
  do
  {
    //send username
    printf("Username: ");
    scanf("%s", username);
    send(client_sock, username, sizeof(username), 0);
    time++;

    //send password
    printf("Password: ");
    scanf("%s", password);
    send(client_sock, password, sizeof(password), 0);

    recv(client_sock, &server_response, sizeof(server_response), 0);
    printf("Tu server: %s\n", server_response);
    if (strcmp(server_response, "User signed in!\n") == 0)
      break;

  } while (time < 3);
  if (time < 3)
  { 
    while (status == 0)
    {
      printf("Them loi nhan: \n");
      scanf("%s", message);
      send(client_sock, message, sizeof(message), 0);
      if(strcmp(message,"bye")==0) return 0;
    }
  }
  return 0;
}
