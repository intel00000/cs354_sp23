#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// global variable for the number of seconds between alarms
int alarm_interval = 4;
// global variable for the number of times SIGUSR1 is received
int SIGUSR1_count = 0;

void SIGALRM_signalHandler()
{
    // Your alarm handler function should get and print the pid (process id) of the program and the current time (in the same format as the Linux date command). return back to the main function, which continues its infinite loop.
    time_t start = time(NULL);
    printf("PID: %d CURRENT TIME: %s", getpid(), ctime(&start));

    // re-arm or restart a new alarm to go off again 4 seconds later
    alarm(alarm_interval);

    // return back to the main function, which continues its infinite loop
    return;
}

void SIGUSR1_signalHandler()
{
    // increment the global counter to keep tally of the number of times it receives SIGUSR1
    SIGUSR1_count++;
    // print a message on receiving a SIGUSR1 signal
    printf("SIGUSR1 handled and counted!\n");

    // return back to the main function, which continues its infinite loop
    return;
}

void SIGINT_signalHandler()
{
    // print the number of times it received the SIGUSR1 signal
    printf("\nSIGINT handled.\n");
    printf("SIGUSR1 was handled %d times. Exiting now.\n", SIGUSR1_count);

    // call exit(0)
    exit(0);
}

int main()
{
    printf("PID and time print every %i seconds.\n", alarm_interval);
    printf("Type Ctrl-C to end the program.\n");

    // First, it sets an alarm that will go off 4 seconds later, causing the kernel to trigger a SIGALRM signal to be sent to the program.
    alarm(alarm_interval);

    struct sigaction SIGALRM_action;
    // memset() is used to set all bytes of action to 0
    memset(&SIGALRM_action, 0, sizeof(SIGALRM_action));
    // set the sa_handler field of SIGALRM_action to the address of SIGALRM_signalHandler function
    SIGALRM_action.sa_handler = SIGALRM_signalHandler;
    // call sigaction() to register the SIGALRM handler
    sigaction(SIGALRM, &SIGALRM_action, NULL);

    struct sigaction SIGUSR1_action;
    // memset() is used to set all bytes of action to 0
    memset(&SIGUSR1_action, 0, sizeof(SIGUSR1_action));
    // set the sa_handler field of SIGUSR1_action to the address of SIGUSR1_signalHandler function
    SIGUSR1_action.sa_handler = SIGUSR1_signalHandler;
    // call sigaction() to register the SIGUSR1 handler
    sigaction(SIGUSR1, &SIGUSR1_action, NULL);

    struct sigaction SIGINT_action;
    // memset() is used to set all bytes of action to 0
    memset(&SIGINT_action, 0, sizeof(SIGINT_action));
    // set the sa_handler field of SIGINT_action to the address of SIGINT_signalHandler function
    SIGINT_action.sa_handler = SIGINT_signalHandler;
    // call sigaction() to register the SIGINT handler
    sigaction(SIGINT, &SIGINT_action, NULL);

    while (1)
    {
    }
    return 0;
}