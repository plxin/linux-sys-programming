#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *th_fun1(void *arg)
{
    printf("thread 1 returning\n");
    return (void *)1;
}

void *th_fun2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void*)2);
}

void *th_fun3(void *arg)
{
    while(1)
    {
        printf("thread 3 writing\n");
        sleep(1);
    }
}

int main(void)
{
    pthread_t tid;
    void *tret;

    pthread_create(&tid, NULL, th_fun1, NULL);
    pthread_join(tid, &tret);
    printf("thread 1 exit code %d\n", (int)tret);

    pthread_create(&tid, NULL, th_fun2, NULL);
    pthread_join(tid, &tret);
    printf("thread 2 exit code %d\n", (int)tret);

    pthread_create(&tid, NULL, th_fun3, NULL);
    sleep(3);
    pthread_cancel(tid);
    pthread_join(tid, &tret);
    printf("thread 3 exit code %d\n", (int)tret);

    return 0;
}
