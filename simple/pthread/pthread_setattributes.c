#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 0x800000

void sys_err(char *str, int exitno)
{
    perror(str);
    exit(exitno);
}

int print_ntimes(char *str)
{
    sleep(1);
    printf("%s", str);
    return 0;
}

void *th_fun(void *arg)
{
    int n = 3;
    while(n--)
        print_ntimes("hello");
}

int main(void)
{
    pthread_t tid;
    int err, detachstate, i = 1;
    pthread_attr_t attr;
    size_t stacksize;
    void *stackaddr;

    pthread_attr_init(&attr);

    pthread_attr_getstack(&attr, &stackaddr, &stacksize);
    printf("stackaddr = %p\n", stackaddr);
    printf("stacksize = %x\n", (int)stacksize);

    pthread_attr_getdetachstate(&attr, &detachstate);

    if(detachstate == PTHREAD_CREATE_DETACHED)
        printf("thread detached\n");
    else if(detachstate == PTHREAD_CREATE_JOINABLE)
        printf("thread join\n");
    else
        printf("thread unknown\n");

    /* 设置线程分离属性 */
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    while(1)
    {
        /* 在堆上申请内存，指定线程栈的起始地址和大小 */
        stackaddr = malloc(SIZE);
        if(stackaddr == NULL)
            sys_err("malloc", 1);

        stacksize = SIZE;
        pthread_attr_setstack(&attr, stackaddr, stacksize);

        err = pthread_create(&tid, &attr, th_fun, NULL);
        if(err != 0)
        {
            printf("%s\n", strerror(err));
            exit(1);
        }
        printf("%d\n", i++);
    }

    pthread_attr_destroy(&attr);
    return 0;
}
