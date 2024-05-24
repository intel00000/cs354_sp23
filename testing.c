#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

int fact(int n)
{
    int result;
    if (n <= 1)
    {
        result = 1;
    }
    else
    {
        result = n * fact(n - 1);
    }

    return result;
}

int main(void)
{
    time_t start = time(NULL);
    printf("PID: %d CURRENT TIME: %s\n", getpid(), ctime(&(start)));

    printf("%d\n", fact(3));

    return 0;
}