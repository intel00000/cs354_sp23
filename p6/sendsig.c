#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    // check number of arguments
    if (argc != 3)
    {
        printf("Usage: sendsig <signal type> <pid>\n");
        exit(0);
    }

    // check input
    if (strcmp(argv[1], "-i") != 0 && strcmp(argv[1], "-u") != 0)
    {
        printf("Usage: sendsig <signal type> <pid>\n");
        exit(0);
    }

    // send the correct signal
    if (strcmp(argv[1], "-i") == 0)
    {
        kill(atoi(argv[2]), SIGINT);
    }
    else if (strcmp(argv[1], "-u") == 0)
    {
        kill(atoi(argv[2]), SIGUSR1);
    }

    return 0;
}