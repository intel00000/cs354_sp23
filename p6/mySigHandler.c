////////////////////////////////////////////////////////////////////////////////
// Main File:        mySigHandler.c
// This File:        mySigHandler.c
// Other Files:      None
// Semester:         CS 354 Spring 2023
// Instructor:       Debra Deppeler
//
// Author:           Tom Tan
// Email:            ztan64@wisc.edu
// CS Login:         ttan
// GG#:              8
//                   (See https://canvas.wisc.edu/groups for your GG number)
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   including family, friencs, classmates, tutors,
//                   Peer Mentors, TAs, and Instructor.
//
// Persons:          None
//
// Online sources:   None
//
////////////////////////////////////////////////////////////////////////////////

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

// SIGALRM Handler
void SIGALRM_Handler()
{
    time_t start = time(NULL);
    // check for time() return value, it should be greater than 0
    if (start < 0)
    {
        printf("Error: time() return.\n");
        exit(1);
    }
    // check ctime() return value, it should not be NULL
    if (ctime(&start) == NULL)
    {
        printf("Error: ctime() return.\n");
        exit(1);
    }
    // print the pid and current time
    printf("PID: %d CURRENT TIME: %s", getpid(), ctime(&start));

    // re-arm a new alarm to go off 4 seconds later
    alarm(alarm_interval);

    // return back to the main function, continues infinite loop
    return;
}

// SIGUSR1 Handler
void SIGUSR1_Handler()
{
    // increment the global counter to keep tally of the number of times it receives SIGUSR1
    SIGUSR1_count++;
    // print a message on receiving a SIGUSR1 signal
    printf("SIGUSR1 handled and counted!\n");

    // return back to the main function, which continues its infinite loop
    return;
}

// SIGINT Handler
void SIGINT_Handler()
{
    // print the number of times it received the SIGUSR1 signal
    printf("\nSIGINT handled.\n");
    printf("SIGUSR1 was handled %d times. Exiting now.\n", SIGUSR1_count);

    // call exit(0)
    exit(0);
}

int main()
{
    // print instructions message
    printf("PID and time print every %i seconds.\n", alarm_interval);
    printf("Type Ctrl-C to end the program.\n");

    // sets an alarm to go off in 4 seconds
    alarm(alarm_interval);

    // register the SIGALRM handler
    struct sigaction SIGALRM_action;
    // memset() is used to set all bytes of action to 0
    memset(&SIGALRM_action, 0, sizeof(SIGALRM_action));
    // set the sa_handler field of SIGALRM_action to the address of SIGALRM_Handler function
    SIGALRM_action.sa_handler = SIGALRM_Handler;
    // call sigaction() to register the SIGALRM handler, and check its return value to make sure that it worked
    if (sigaction(SIGALRM, &SIGALRM_action, NULL) != 0)
    {
        printf("Error: SIGALRM handler registration failed.\n");
        exit(1);
    }

    // register the SIGUSR1 handler
    struct sigaction SIGUSR1_action;
    // memset() is used to set all bytes of action to 0
    memset(&SIGUSR1_action, 0, sizeof(SIGUSR1_action));
    // set the sa_handler field of SIGUSR1_action to the address of SIGUSR1_Handler function
    SIGUSR1_action.sa_handler = SIGUSR1_Handler;
    // call sigaction() to register the SIGUSR1 handler, check return value
    if (sigaction(SIGUSR1, &SIGUSR1_action, NULL) != 0)
    {
        printf("Error: SIGUSR1 handler registration failed.\n");
        exit(1);
    }

    // register the SIGINT handler
    struct sigaction SIGINT_action;
    // memset() is used to set all bytes of action to 0
    memset(&SIGINT_action, 0, sizeof(SIGINT_action));
    // set the sa_handler field of SIGINT_action to the address of SIGINT_Handler function
    SIGINT_action.sa_handler = SIGINT_Handler;
    // call sigaction() to register the SIGINT handler, check return value
    if (sigaction(SIGINT, &SIGINT_action, NULL) != 0)
    {
        printf("Error: SIGINT handler registration failed.\n");
        exit(1);
    }

    // empty infinite loop
    while (1)
    {
    }

    return 0;
}