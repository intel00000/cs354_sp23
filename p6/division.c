////////////////////////////////////////////////////////////////////////////////
// Main File:        division.c
// This File:        division.c
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

// global variable for the number of successful division operations
int successful_divisions = 0;

// SIGFPE handler
void SIGFPE_Handler()
{
    // print a message on receiving a SIGFPE signal
    printf("Error: a division by 0 operation was attempted.\n");
    printf("Total number of operations completed successfully: %d\n", successful_divisions);
    printf("The program will be terminated.\n");

    // gracefully exit the program
    exit(0);
}

// SIGINT handler
void SIGINT_Handler()
{
    // print the number of successful division operations
    printf("\nTotal number of operations completed successfully: %d\n", successful_divisions);
    printf("The program will be terminated.\n");

    // gracefully exit the program
    exit(0);
}

int main()
{

    // handle SIGFPE signals
    struct sigaction SIGFPE_action;
    // memset() is used to set all bytes of action to 0
    memset(&SIGFPE_action, 0, sizeof(SIGFPE_action));
    // set the sa_handler field of SIGFPE_action to the address of SIGFPE_Handler function
    SIGFPE_action.sa_handler = SIGFPE_Handler;
    // call sigaction() to register the SIGFPE handler, check return value
    if (sigaction(SIGFPE, &SIGFPE_action, NULL) != 0)
    {
        printf("Error: SIGFPE handler registration failed.\n");
        exit(1);
    }

    // handle SIGINT signals
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

    // infinite loop
    while (1)
    {
        // Prompt for and read in the first integer value.
        char buffer[100];
        printf("Enter first integer: ");
        // check fgets() return value, it should not be NULL
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            printf("Error: fgets() return.\n");
            exit(1);
        }
        int firstInt = atoi(buffer);

        // Prompt for and read in the second integer value.
        printf("Enter second integer: ");
        // check fgets() return value, it should not be NULL
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            printf("Error: fgets() return.\n");
            exit(1);
        }
        int secondInt = atoi(buffer);

        // Calculate the quotient and remainder of doing the integer division operation: int1 / int2.
        int quotient = firstInt / secondInt;
        int remainder = firstInt % secondInt;

        // Increment the global counter
        successful_divisions++;

        // Print the results.
        printf("%d / %d is %d with a remainder of %d\n", firstInt, secondInt, quotient, remainder);
    }

    return 0;
}