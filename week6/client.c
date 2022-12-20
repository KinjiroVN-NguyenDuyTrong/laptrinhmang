#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define BUFF_SIZE 1024
int main(int argc, char *argv[])
{
  if (argc != 3){
        printf("Usage: %s <Server IP> <Server Port>\n", argv[0]);
        return 0;
    }
  int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[BUFF_SIZE];

  char username[30],password[30];
  int time = 0;

  char SERV_IP[16];
  int SERV_PORT;

  strcpy(SERV_IP, argv[1]);
  SERV_PORT = atoi(argv[2]);

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	
  if(clientSocket < 0){
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERV_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERV_IP);

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Connected to Server.\n");

	do
  {
    //send username
    printf("Username: ");
    scanf("%s", username);
    send(clientSocket, username, sizeof(username), 0);
    time++;

    //send password
    printf("Password: ");
    scanf("%s", password);
    send(clientSocket, password, sizeof(password), 0);

    recv(clientSocket, &buffer, sizeof(buffer), 0);
    printf("Tu server: %s\n", buffer);
    if (strcmp(buffer, "User signed in!\n") == 0)
      break;

  } while (time < 3);

	return 0;
}
