#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>


#define LENGTH 2048

// Global variables
volatile sig_atomic_t flag = 0;
int sockfd = 0;
char name[32];
char pass[32];

bool login(){
    char buffer[1024];
    //send username
    printf("User name: ");
    fgets(name, 32, stdin);
    str_trim_lf(name, strlen(name));
    send(sockfd, name, 32, 0);

    //send password
    printf("Password: ");
    fgets(pass, 32, stdin);
    str_trim_lf(pass, strlen(pass));
    send(sockfd, pass, 32, 0);

    recv(sockfd, &buffer, sizeof(buffer), 0);
    printf("Tu server: %s\n", buffer);

    if(strcmp(buffer,"User signed in!\n")!=0)
    return false;

    return true;
}

void str_overwrite_stdout() {
  printf("%s", "> ");
  fflush(stdout);
}

void str_trim_lf (char* arr, int length) {
  int i;
  for (i = 0; i < length; i++) { // trim \n
    if (arr[i] == '\n') {
      arr[i] = '\0';
      break;
    }
  }
}

void catch_ctrl_c_and_exit(int sig) {
    flag = 1;
}

void send_msg_handler() {
    char message[LENGTH] = {};
    char buffer[LENGTH + 32] = {};

    while(1) {
  	str_overwrite_stdout();
    fgets(message, LENGTH, stdin);
    str_trim_lf(message, LENGTH);

    if (strcmp(message, "exit") == 0) {
			break;
    } else {
      sprintf(buffer, "%s: %s\n", name, message);
      send(sockfd, buffer, strlen(buffer), 0);
    }

	bzero(message, LENGTH);
    bzero(buffer, LENGTH + 32);
  }
  catch_ctrl_c_and_exit(2);
}

void recv_msg_handler() {
	char message[LENGTH] = {};
    while (1) {
		int receive = recv(sockfd, message, LENGTH, 0);
    if (receive > 0) {
      printf("%s", message);
      str_overwrite_stdout();
    } else if (receive == 0) {
			break;
    } else {
			// -1
		}
		memset(message, 0, sizeof(message));
  }
}

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("Usage: %s <Server IP> <Server Port>\n", argv[0]);
		return EXIT_FAILURE;
	}

	char SERV_IP[16];
    strcpy(SERV_IP, argv[1]);
	int port = atoi(argv[2]);

	signal(SIGINT, catch_ctrl_c_and_exit);


	struct sockaddr_in server_addr;

	/* Socket settings */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Client Socket is created.\n");

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(SERV_IP);



    // Connect to Server
    int err = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (err == -1) {
	  	printf("ERROR: connect\n");
	  	return EXIT_FAILURE;
	  }

  	// login
    if(login()==false)
    return EXIT_FAILURE;


    str_trim_lf(name, strlen(name));

	  printf("=== WELCOME TO THE CHATROOM ===\n");
    readFile();

	  pthread_t send_msg_thread;
    if(pthread_create(&send_msg_thread, NULL, (void *) send_msg_handler, NULL) != 0){
		  printf("ERROR: pthread\n");
      return EXIT_FAILURE;
	  }

	  pthread_t recv_msg_thread;
    if(pthread_create(&recv_msg_thread, NULL, (void *) recv_msg_handler, NULL) != 0){
	  	printf("ERROR: pthread\n");
	  	return EXIT_FAILURE;
	  }

	while (1){
		if(flag){
			printf("\nBye\n");
			break;
    }
	}

	close(sockfd);

	return EXIT_SUCCESS;
}