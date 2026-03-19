#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <sys/ioctl.h>
#include <netinet/tcp.h>
#include <linux/sockios.h>
#include <unistd.h> // read(), write(), close()
#include <arpa/inet.h>

#define SIZE (256*1024)
#define PORT 8090

#define SA struct sockaddr 

uint8_t buff[SIZE];

void func(int connfd)
{
    int maxQlen = 0;
    for (;;) {
       int value;
       if(ioctl(connfd, SIOCINQ, &value) >=0 ) {
          if(value > maxQlen) {
             maxQlen = value;
             printf("Max rx q len %d\n", maxQlen);
          }
        }
        read(connfd, buff, sizeof(buff));
    }
}


int main() 
{ 
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
   
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
   
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
   
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
   
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    len = sizeof(cli); 
   
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server accept failed...\n"); 
        exit(0); 
    } 
    else {
        char str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(cli.sin_addr), str, INET_ADDRSTRLEN);
        printf("server accept the client from %s...\n", str); 
    }
   
    int on = 1;
    setsockopt(sockfd, SOL_TCP, TCP_NODELAY, &on, sizeof(on));

    int nrx,ntx;
    unsigned int m = sizeof(nrx);
    getsockopt(connfd,SOL_SOCKET,SO_RCVBUF,(void *)&nrx, &m);
    getsockopt(connfd,SOL_SOCKET,SO_SNDBUF,(void *)&ntx, &m);
    printf("Socket send buffer %d, recieve buffer %d\n", ntx, nrx);
    // Function for chatting between client and server 
    func(connfd); 
   
    // After chatting close the socket 
    close(sockfd); 
}

