#define _GNU_SOURCE 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <assert.h>


#define BUFFER_SIZE 64

void err_exit(const char *str, int errn)
{
    perror(str);
    exit(errn);
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("usage: %s is ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_address.sin_addr);
    server_address.sin_port =  htons(port);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        err_exit("socket", 1);
    // assert(sockfd >= 0);
    if(connect(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        printf("connection failed\n");
        close(sockfd);
        return 1;
    }

    struct pollfd fds[2];
    /*  注册文件描述符0(标准输入)和文件描述符sockfd上的可读事件 */ 
    fds[0].fd = 0;
    fds[0].events = POLLIN;
    fds[0].revents = 0;

    fds[1].fd = sockfd;
    fds[1].events = POLLIN | POLLRDHUP;
    fds[1].revents = 0;

    char read_buf[BUFFER_SIZE];
    int pipefd[2];
    int ret = pipe(pipefd);
    if(ret == -1)
        err_exit("pipe", 1);
    // assert( ret != -1);
    while (1)
    {
        ret = poll(fds, 2, -1);
        if(ret < 0)
        {
            printf("poll failed\n");
            break;
        }
        if(fds[1].revents & POLLRDHUP)
        {
            printf("server close the connection\n");
            break;
        }
        else if(fds[1].revents & POLLIN)
        {
            memset(read_buf, '\0', BUFFER_SIZE);
            recv(fds[1].fd, read_buf, BUFFER_SIZE -1, 0);
            printf("Client receive: %s\n", read_buf);
        }
        if(fds[0].revents & POLLIN)
        {
            /* 使用splice将用户输入的数据直接写到sockfd上(零拷贝) */
            ret = splice(0, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
            ret = splice(pipefd[0], NULL, sockfd, NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
        }
    }
    close(sockfd);
    return 0;
}