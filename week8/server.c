#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char **argv) {
	
	fd_set fds, readfds;
	char buf[1024];
	int i, clientaddrlen,rval;
	int clientsock[2], rc, numsocks = 0, maxsocks = 5;
	int serversock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	
		perror("Socket");
	struct sockaddr_in serveraddr, clientaddr;  
	bzero(&serveraddr, sizeof(struct sockaddr_in));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(6782);
	if (-1 == bind(serversock, (struct sockaddr *)&serveraddr,sizeof(struct sockaddr_in))) 
		perror("Bind");
	
	if (-1 == listen(serversock, SOMAXCONN))
		perror("Listen");
    //clears a set.
	FD_ZERO(&fds);
    //add a given file descriptor from a set
    FD_SET(serversock, &fds);
    printf(" Our Server is Listening !\n");
    while(1) {
    	readfds = fds;
        rc = select(FD_SETSIZE, &readfds, NULL, NULL, NULL);
        //test if there are a error
        if (rc == -1) {
        	perror("Select");
        	break;
        }//---------------------------------------
        for (i = 0; i < FD_SETSIZE; i++) {

        	if (FD_ISSET(i, &readfds)){
        		
        		if (i == serversock){
        			
        			if (numsocks < maxsocks){
        				clientsock[numsocks] = accept(serversock,(struct sockaddr *) &clientaddr,(socklen_t *)&clientaddrlen);
        				if (clientsock[numsocks] == -1)
        				 perror("Accept");
        				FD_SET(clientsock[numsocks], &fds);
        				numsocks++;
        			}else{
        				printf("Ran out of socket space.\n");
        				goto out;
        			}
        		}else{
        			bzero(buf, sizeof(buf));
        			if ((rval = read(i, buf, 1024)) < 0){
        				perror("reading stream message");
        				goto out;
        			}
        			else if (rval == 0){
        				printf("Ending connection\n");
        				goto out;
        			}
        			else
        				printf("-->%s\n", buf);
        		}
        	}
        }
    }
    out:close(serversock);
    return 0;
}