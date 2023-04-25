#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
    // set errno flag
    errno = ENOENT;

    printf("%s\n", strerror(errno));

    time_t start = time(NULL);
    printf("PID: %d CURRENT TIME: %s\n", getpid(), ctime(&(start)));

    return 0;
}