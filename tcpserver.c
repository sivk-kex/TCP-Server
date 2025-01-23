#include "common.h"
#include <netinet/in.h>
#include <strings.h>


int main (int argc, char **argv){ 


    //using port 18000
    int         listenfd, connfd, n ; 
    struct sockaddr_in  serveraddr  ; 
    uint8_t     buff[MAXLINE+1]; 
    uint8_t     recvline[MAXLINE+1] ;

    //allocating resources
    listenfd = socket(AF_INET, SOCK_STREAM, 0); 


    //settings
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family=AF_INET; 
    serveraddr.sin_addr.s_addr=htonl(INADDR_ANY); 
    serveraddr.sin_port=htons(SERVER_PORT); 

    //bind and listen 
    if(bind(listenfd, (SA *)&serveraddr, sizeof(serveraddr))>0){}
    listen(listenfd, 10); 

    //connection and responding 
    for( ; ;){ 
        // struct sockaddr_in addr; 
        // socklen_t addrlen ; 
        printf("Awaiting connection on %d", SERVER_PORT);
        fflush(stdout); 
        connfd= accept(listenfd , (SA *)NULL, NULL) ;
        //will now fork the proc 
        pid_t PID= fork(); 
        if(PID==0){ 
        memset(recvline, 0,MAXLINE);

        while((n = read(connfd, recvline,MAXLINE-1))>0){ 
            fprintf(stdout, "%s",recvline); 
            //cool trick
            if(recvline[n-1]=='\n'){
                break;
            }
        } 
        memset(recvline,0,MAXLINE); 

    }
    snprintf((char*)buff,sizeof(buff), "HTTP/1.0 200 OK \r\n\r\n Hello World");

    write (connfd , (char*)buff, sizeof(buff)); 
            
        }

    close(connfd); 



}