#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>
#include <linux/sockios.h>
#include <unistd.h> // read(), write(), close()

#define SIZE (256*1024)
#define PORT 8090

#define SA struct sockaddr

uint8_t buf[SIZE];

u_int64_t monoUsec(void)
{
    u_int64_t microsec;
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    microsec = (u_int64_t)ts.tv_sec * 1000000 +
                       ts.tv_nsec / 1000;

    return microsec;
}

int verifyIP(char *ipStr)
{
    struct sockaddr_in sa;
    if(inet_pton(AF_INET, ipStr, &(sa.sin_addr)) != 1) {
        return 0;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    int sockfd, connfd;
    int isConnected = 0;
    struct sockaddr_in servaddr, cli;
    fd_set socketsFD;
    int  bufOffset = 0;
    int sizeToWrite = SIZE;
    long count = 0;
    int maxQlen = 0;
    int maxSndBuf = 0;
    int notFullWrt = 0;
    int maxQpercent = 0;
    u_int64_t startTime = monoUsec();

    if(argc < 2) {
        printf("Usage %s <remote-IP> [<local-IP]\n", argv[0]);
        return 0;
    }

    if(verifyIP(argv[1]) != 1) {
        printf("Invalid IP address: %s\n", argv[1]);
        return 0;
    }

    if(argc > 2 && verifyIP(argv[2]) != 1) {
        printf("Invalid IP address: %s\n", argv[2]);
        return 0;
    }

    bzero(buf, SIZE);

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    if(argc > 2) {
        struct sockaddr_in cliaddr;
        bzero(&cliaddr, sizeof(cliaddr));

        // assign IP, PORT
        cliaddr.sin_family = AF_INET;
        cliaddr.sin_addr.s_addr = inet_addr(argv[2]);
        cliaddr.sin_port = 0;

        // Binding newly created socket to given source IP and verification
        if ((bind(sockfd, (SA*)&cliaddr, sizeof(servaddr))) != 0) {
            printf("client socket bind failed...\n");
            exit(0);
        }
        else
            printf("Socket successfully binded..\n");
    }

    bzero(&servaddr, sizeof(servaddr));
 
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]); //"127.0.0.1");
    servaddr.sin_port = htons(PORT);

    int rc = connect(sockfd, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    if(rc == 0)
        isConnected = 1;
    else {
        while(1) {
           FD_ZERO(&socketsFD);
           FD_SET(sockfd, &socketsFD);

           rc = select(sockfd + 1, NULL, &socketsFD, NULL, NULL);
           if(rc >=0 ) {
               if (FD_ISSET(sockfd, &socketsFD)) {
                   printf("Socket is ready for write!  Let's find out if the connection succeeded or not...\n");

                   struct sockaddr_in junk;
                   socklen_t length = sizeof(junk);
                   memset(&junk, 0, sizeof(junk));
                   if (getpeername(sockfd, (struct sockaddr *)&junk, &length) == 0)
                   {
                      printf("TCP Connection succeeded, socket is ready for use!\n");
                      break;
                   }
                   else
                   {
                      printf("TCP Connection failed!\n");
                      close(sockfd);
                      return 0;
                   }
               }
           }
           else {
               printf("Connect select error\n");
               close(sockfd);
               return 0;
           }
        }

    }
    int on = 1;
    setsockopt(sockfd, SOL_TCP, TCP_NODELAY, &on, sizeof(on));

    int nrx,ntx;
    unsigned int m = sizeof(nrx);
    ntx = 6291456;
    //setsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,(void *)&ntx, m);
    getsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,(void *)&nrx, &m);
    getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,(void *)&ntx, &m);
    printf("Socket send buffer %d, recieve buffer %d\n", ntx, nrx);
    printf("Write some buffers\n");
    for(int iter = 0; iter < 2; ) {
       FD_ZERO(&socketsFD);
       FD_SET(sockfd, &socketsFD);

       rc = select(sockfd + 1, NULL, &socketsFD, NULL, NULL);
       if(rc >=0 ) {
           if (FD_ISSET(sockfd, &socketsFD)) {
               rc = write(sockfd, buf + bufOffset, sizeToWrite);
               if(rc > 0) {
                  int value;
                  if(ioctl(sockfd, SIOCOUTQ, &value) >=0 ) {
                      if(value > maxQlen)
                          maxQlen = value;
                  }
                  getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,(void *)&ntx, &m);
                  if(ntx > maxSndBuf)
                      maxSndBuf = ntx;
                  if(value * 100 / ntx > maxQpercent)
                      maxQpercent = value * 100 / ntx;

                  if(rc < sizeToWrite)
                      notFullWrt++;

                  sizeToWrite -= rc;
                  bufOffset += rc;
                  if(sizeToWrite == 0) {
                      bufOffset = 0;
                      sizeToWrite = SIZE;
                      count++;
                      if(monoUsec() - startTime > 5000000) {
                          printf("Sent %lu buffers in 5 secs, max q len %d, max send buf size %d, non-full writes %d, max q full %% %d\n", count, maxQlen, maxSndBuf, notFullWrt, maxQpercent);
                          startTime = monoUsec();
                          count = 0;
                          maxQlen = 0;
                          maxSndBuf = 0;
                          notFullWrt = 0;
                          maxQpercent = 0;
                          iter ++;
                      }
                  }
               }
           }
       }
       else {
           printf("Write select error\n");
           close(sockfd);
           return 0;
       }
    }
    close(sockfd);
}
