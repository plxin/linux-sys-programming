#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void *th_fun(void *arg)
{
    int *p = (int *)arg;
    printf("thread PID = %d\n", getpid());
    printf("thread ID = %x\n", (unsigned int)pthread_self());
    printf("*arg = %d\n", *p);
    sleep(1);
}

int main(void)
{
    pthread_t tid;
    int n = 10;
    pthread_create(&tid, NULL, th_fun, (void*)&n);

    printf("main thread Id = %x\n", (unsigned int)pthread_self());
    printf("main child thread ID = %x\n", (unsigned int)tid);
    printf("main PID = %d\n", getpid());
    sleep(2);
    return 0;

}
