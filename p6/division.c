#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// global variable for the number of successful division operations
int successful_divisions = 0;

void SIGFPE_signalHandler()
{
    // print a message on receiving a SIGFPE signal
    printf("Error: a division by 0 operation was attempted.\n");
    printf("Total number of operations completed successfully: %d\n", successful_divisions);
    printf("The program will be terminated.\n");

    // gracefully exit the program
    exit(0);
}

void SIGINT_signalHandler()
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
    // set the sa_handler field of SIGFPE_action to the address of SIGFPE_signalHandler function
    SIGFPE_action.sa_handler = SIGFPE_signalHandler;
    // call sigaction() to register the SIGFPE handler
    sigaction(SIGFPE, &SIGFPE_action, NULL);

    // handle SIGINT signals
    struct sigaction SIGINT_action;
    // memset() is used to set all bytes of action to 0
    memset(&SIGINT_action, 0, sizeof(SIGINT_action));
    // set the sa_handler field of SIGINT_action to the address of SIGINT_signalHandler function
    SIGINT_action.sa_handler = SIGINT_signalHandler;
    // call sigaction() to register the SIGINT handler
    sigaction(SIGINT, &SIGINT_action, NULL);

    while (1)
    {
        // Prompt for and read in the first integer value.
        char buffer[100];
        printf("Enter first integer: ");
        fgets(buffer, sizeof(buffer), stdin);
        int firstInt = atoi(buffer);

        // Prompt for and read in the second integer value.
        printf("Enter second integer: ");
        fgets(buffer, sizeof(buffer), stdin);
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