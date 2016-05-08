#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 256
#define STDIN 0
#define STDOUT 1
#define INVALID -1

int main()
{
    //建立并连接socket
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in srv;
    bzero(&srv,sizeof(srv));
    srv.sin_addr.s_addr = inet_addr("127.0.0.1");
    srv.sin_family = AF_INET;
    srv.sin_port = htons(5888);
    if (connect(sockfd, (struct sockaddr *)&srv, sizeof(srv))== INVALID)
    {
        puts("connection fail\n");
        exit(1);
    }
    else
    {
        puts("connection succeed\n");
    }

    //select实现I/O复用
    fd_set fdset;
    char buffer[BUF_SIZE];
    int i,read_stat;
    while(1)
    {
        FD_ZERO(&fdset);
        FD_SET(STDIN,&fdset);
        FD_SET(sockfd,&fdset);
        select(sockfd+1,&fdset,NULL,NULL,NULL);

        if(FD_ISSET(sockfd,&fdset))
        {
            read_stat=read(sockfd,buffer,BUF_SIZE);
            if(read_stat==0)
            {
                puts("server closed");
                exit(1);
            }
            else if(read_stat>0)
                write(STDOUT,buffer,read_stat);
            else
            {
                puts("read error");
                exit(1);
            }

        }
        else if(FD_ISSET(STDIN, &fdset))
        {
            read_stat=read(STDIN,buffer,BUF_SIZE);
            write(sockfd,buffer,read_stat);
        }
    }
    return 0;
}

