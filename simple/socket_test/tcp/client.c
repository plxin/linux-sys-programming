#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>


#define SERVER_PORT 8000
#define MAXLINE 4096
int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("./client str\n");
        exit(1);
    }
    
    int confd, len;
    char buf[MAXLINE];
    struct sockaddr_in serveraddr;
    char ipstr[] = "222.20.101.246";
    // 1.创建一个socket
    confd = socket(AF_INET, SOCK_STREAM, 0);
    // 2.初始化服务器地址
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    // 
    inet_pton(AF_INET, ipstr, &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(SERVER_PORT);
    // 3.连接服务器
    connect(confd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    // 4.请求服务器处理数据
    write(confd, argv[1], strlen(argv[1]));
    len = read(confd, buf, sizeof(buf));
    write(STDOUT_FILENO, buf, len);
    // 5.关闭socket
    close(confd);
    return 0;
}