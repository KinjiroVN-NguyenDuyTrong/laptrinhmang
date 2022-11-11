#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

#define BUFF_SIZE 8192

int main(int argc, char *argv[]){
	if (argc != 3){
        printf("Usage: %s <Server IP> <Server Port>\n", argv[0]);
        return 0;
    }

	int client_sock;
	char buff[BUFF_SIZE],server_response[256];
	struct sockaddr_in server_addr; /* server's address information */
	int msg_len, bytes_sent, bytes_received;
	
	char SERV_IP[16];
    int SERV_PORT;

	strcpy(SERV_IP, argv[1]);
    SERV_PORT = atoi(argv[2]);
	//Step 1: Construct socket
	if((client_sock=socket(AF_INET, SOCK_STREAM, 0)) < 0){
        // Call socket() to create a socket
        perror("\nError: ");
        return 0;
    }
	
	//Step 2: Specify server address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERV_PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERV_IP);
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
	//printf("iu meo");
	printf("Tu server: %s \n",server_response);
		
	//Step 4: Communicate with server			
	while(1){
		//send message
		printf("\nInsert string to send:");
		memset(buff,'\0',(strlen(buff)+1));
		fgets(buff, BUFF_SIZE, stdin);		
		msg_len = strlen(buff);
		if (msg_len == 0) break;
		
		bytes_sent = send(client_sock, buff, msg_len, 0);
		if(bytes_sent <= 0){
			printf("\nConnection closed!\n");
			break;
		}
		
		//receive echo reply
		bytes_received = recv(client_sock, buff, BUFF_SIZE-1, 0);
		if(bytes_received <= 0){
			printf("\nError!Cannot receive data from sever!\n");
			break;
		}
		
		buff[bytes_received] = '\0';
		printf("Reply from server: %s \n", buff);
	}
	
	//Step 4: Close socket
	close(client_sock);
	return 0;
}
