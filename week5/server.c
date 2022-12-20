#include <stdio.h>          /* These are the usual header files */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


#define BACKLOG 5   /* Number of allowed connections */
#define BUFF_SIZE 1024

void string_process(char *buff, char *character, char *number){
    // If received string include non-digit or non-alphabet character, 
    // return error message
    int i;
    // Ignore the last character "\n"
    buff[strlen(buff)-1] = '\0';
    
    for (i = 0; i < strlen(buff); i++){
        if (isdigit(buff[i]) == 0 && isalpha(buff[i]) == 0){
            strcpy(buff, "Error\0");
            return;
        }
    }
    // Split received string into character and number sub-string
    int j = 0;
    int k = 0;
    for (i = 0; i < strlen(buff); i++){
        if (isdigit(buff[i]) != 0){
            number[j] = buff[i];
            j++;
        }
        else{
            character[k] = buff[i];
            k++;
        }
    }
    // Copy character and number sub-string to buff
    strcpy(buff, number);
    strcat(buff, "\n");
    strcat(buff, character);
    buff[strlen(buff)] = '\0';
    // printf("\nbuff: %s", buff);
    
}

int main(int argc, char *argv[])
{
 
	int listen_sock, conn_sock; /* file descriptors */
	char recv_data[BUFF_SIZE];
	int bytes_sent, bytes_received;
	int port = atoi(argv[1]); //server port
	struct sockaddr_in server; /* server's address information */
	struct sockaddr_in client; /* client's address information */
	int sin_size;
	char server_mesg[256] = "Server connected successfully!\n";

	//Step 1: Construct a TCP socket to listen connection request
	if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  /* calls socket() */
		perror("\nError: ");
		return 0;
	}
	
	//Step 2: Bind address to socket
	//bzero(&server, sizeof(server));
	server.sin_family = AF_INET;         
	server.sin_port = htons(port);   /* Remember htons() from "Conversions" section? =) */
	server.sin_addr.s_addr = htonl(INADDR_ANY);  /* INADDR_ANY puts your IP address automatically */   
	if(bind(listen_sock, (struct sockaddr*)&server, sizeof(server))==-1){ /* calls bind() */
		perror("\nError: ");
		return 0;
	}     
	printf("\nServer is running on port %d\n",port);
	
	//Step 3: Listen request from client
	if(listen(listen_sock, BACKLOG) == -1){  /* calls listen() */
		perror("\nError: ");
		return 0;
	}
	conn_sock=accept(listen_sock, NULL, NULL);
	send(conn_sock, server_mesg, sizeof(server_mesg), 0);
	//Step 4: Communicate with client
	while(1){
		//accept request
		sin_size = sizeof(struct sockaddr_in);
		if ((conn_sock = accept(listen_sock,( struct sockaddr *)&client, &sin_size)) == -1) 
			perror("\nError: ");
  
		printf("You got a connection from %s\n", inet_ntoa(client.sin_addr) ); /* prints client's IP */
		
		//start conversation
		while(1){
			//receives message from client
			bytes_received = recv(conn_sock, recv_data, BUFF_SIZE-1, 0); //blocking
			if (bytes_received <= 0){
				printf("\nConnection closed\n");
				break;
			}
			else{
				recv_data[bytes_received] = '\0';
				printf("\nReceive: %s ", recv_data);
			}
			
			//echo to client
			bytes_sent = send(conn_sock, recv_data, bytes_received, 0); /* send to the client welcome message */
			if (bytes_sent <= 0){
				printf("\nConnection closed\n");
				break;
			}
		}//end conversation
		close(conn_sock);	
	}
	
	close(listen_sock);
	return 0;
}