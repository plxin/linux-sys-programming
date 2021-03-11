#include <stdio.h>
#include <unistd.h>

int main()
{
    int cnt;
    alarm(1);
    for(cnt = 0; 1; cnt++)
        printf("cnt=%d ", cnt);

    return 0;
}
