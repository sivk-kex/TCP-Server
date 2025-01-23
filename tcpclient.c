
//to-do : make err fn 



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <sys/time.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <netdb.h>

#define SERVER_PORT 80
#define MAXLINE     4096
#define SA struct sockaddr 



int main (int argc, char **argv){ 
    
    int         sockfd;
    int         n;
    int         sendbytes;
    struct sockaddr_in      server_addr;
    char        sendline[MAXLINE];
    char        recvline[MAXLINE]; 


    if((sockfd=socket(AF_INET, SOCK_STREAM, MAXLINE-1))<0){ 
        //error log 

    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(SERVER_PORT); 

    if(inet_pton(AF_INET, argv[1],&server_addr.sin_addr)<=0){
        //error log 
    }
    if(connect(sockfd, (SA *)&server_addr, sizeof(server_addr))<0){}

    sprintf(sendline, "GET / HTTP 1.1/r/n/r/n"); 
     sendbytes = strlen(sendline); 

    write(sockfd, sendline ,sendbytes); 
    read(sockfd, recvline, MAXLINE-1);
    memset(recvline, 0, MAXLINE); 
    while( (n= read(sockfd, recvline, MAXLINE-1))>0){ 
        printf("%s",recvline); 
    }
    printf("TCP Client started successfully");
    exit(0); 


}




void err_n_die (const char *fmt, ...) {

    
}