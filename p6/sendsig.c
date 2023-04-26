////////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c
// This File:        sendsig.c
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
        // check kill return value, it should be 0
        if (kill(atoi(argv[2]), SIGINT) != 0)
        {
            printf("Error: kill() return.\n");
            exit(1);
        }
    }
    else if (strcmp(argv[1], "-u") == 0)
    {
        // check kill return value, it should be 0
        if (kill(atoi(argv[2]), SIGUSR1) != 0)
        {
            printf("Error: kill() return.\n");
            exit(1);
        }
    }

    return 0;
}