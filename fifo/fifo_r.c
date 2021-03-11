#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

void sys_err(char *str, int exitno)
{
    perror("str");
    exit(exitno);
}

int main(int argc, char *argv[])
{
    int fd, len;
    // char buf[1024] = "hello, world\n";
    
    char buf[1024];
    if(argc < 2)
    {
        printf("./fifo_r fifoname");
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    if(fd < 0)
        sys_err("open", 1);
    
    len = read(fd, buf, sizeof(buf));
    write(STDOUT_FILENO, buf, len);
    // write(fd, buf, strlen(buf));
    close(fd);
    
    return 0;
}
