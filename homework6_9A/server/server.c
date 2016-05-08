#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>

#define BUF_SIZE 256
#define IP_SIZE 16
#define CLIENT_SIZE 50
#define TIME_SIZE 16
#define INVALID -1
struct CLIENT
{
    int clienfd;
    struct sockaddr_in sockaddr;
    char ip[IP_SIZE];
    int port;
} clients[CLIENT_SIZE];

void printmsg(int i, char *buffer, const char *msg)
{
    char curtime[TIME_SIZE];
    time_t curtime_t;
    struct tm *timeinfo;
    time(&curtime_t);
    timeinfo = localtime(&curtime_t);
    strftime(curtime, TIME_SIZE, "%X", timeinfo);
    sprintf(buffer,"<%s %s:%d> %s",curtime,clients[i].ip,clients[i].port,msg);
}

void broadcast_msg(char *buffer)
{   int j;
    for(j = 0; j<CLIENT_SIZE; j++)
            {
                if( clients[j].clienfd!= INVALID )
                {
                    write(clients[j].clienfd, buffer, strlen(buffer));
                }
            }

}

void register_client(int listenfd)
{
    int connectfd,i;
    char buffer[BUF_SIZE];
    struct sockaddr_in clientaddr;
    socklen_t connectlen = sizeof(struct sockaddr_in);
    connectfd = accept( listenfd, (struct sockaddr *)&clientaddr, &connectlen);

    for( i = 0; i < CLIENT_SIZE;i++ )
    {
        if(clients[i].clienfd == INVALID)
        {
            clients[i].clienfd = connectfd;
            memcpy(&clients[i].sockaddr,&clientaddr,connectlen);
            clients[i].port = ntohs(clients[i].sockaddr.sin_port);
            inet_ntop(AF_INET, &clients[i].sockaddr.sin_addr, clients[i].ip, IP_SIZE);
            printmsg(i,buffer,"login\n");
            printf("%s",buffer);
            // broadcast login msg
            broadcast_msg(buffer);
            break;
        }
    }
    if (i == CLIENT_SIZE )
    {
        strcpy(buffer, "surpass user's max number\n");
        write(connectfd, buffer, strlen(buffer));
        close(connectfd);
    }
}

void broadcast_client(fd_set fdset)
  {
      int sockfd, read_stat, i;
      char read_buf[BUF_SIZE], send_buf[BUF_SIZE];

      for( i = 0; i < CLIENT_SIZE; i++ )
      {
         sockfd = clients[i].clienfd;
         if(sockfd != INVALID && FD_ISSET(sockfd,&fdset))
         {
             read_stat = read(sockfd, read_buf, BUF_SIZE - 1);
             if(read_stat == 0)
             {
                 //connection lost
                 close(sockfd);
                 clients[i].clienfd = INVALID;
                 printmsg(i, send_buf, "logout\n");
                 printf("%s\n",send_buf);
                 broadcast_msg(send_buf);
                 continue;
             }
             else
             {
                 read_buf[read_stat] = '\0';
                 printmsg(i, send_buf, read_buf);
                 printf("%s",send_buf);
                 broadcast_msg(send_buf);             }
         }
     }
 }

int main()
{
    int i,maxfd;
    //初始化客户端
    for( i = 0; i < CLIENT_SIZE; i++ )
    {
        clients[i].clienfd = INVALID;
    }

//建立，绑定，监听socket
int listenfd=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in srv;
bzero(&srv,sizeof(srv));
srv.sin_addr.s_addr = htonl(INADDR_ANY);
srv.sin_family = AF_INET;
srv.sin_port = htons(5888);
//bind
if (bind(listenfd, (struct sockaddr *)&srv, sizeof(srv))== INVALID)
{
    puts("bind fail\n");
    exit(1);
}
else
    puts("bind succeed\n");
//listen
if(listen(listenfd,CLIENT_SIZE) == INVALID)
{
    puts("listen error\n");
    exit(1);
}
else
    puts("listen succeed\n");
puts("service setup\n");

//select实现I/O复用
fd_set fdset;
while(1)
{
    FD_ZERO(&fdset);
    FD_SET(listenfd, &fdset);
    maxfd = listenfd;
    for(i = 0; i < CLIENT_SIZE; i++)
    {
        if(clients[i].clienfd != INVALID)
        {
            FD_SET(clients[i].clienfd, &fdset);
            if(clients[i].clienfd > maxfd)
                maxfd = clients[i].clienfd;
        }
    }
    select(maxfd + 1, &fdset, NULL, NULL, 0);
    if(FD_ISSET(listenfd, &fdset))
        register_client(listenfd);
    else
        broadcast_client(fdset);
}


return 0;
}

