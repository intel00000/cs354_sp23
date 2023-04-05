////////////////////////////////////////////////////////////////////////////////
// Main File:        sequence.c
// This File:        sequence.c
// Other Files:      None
// Semester:         CS 354 Lecture 002 Spring 2023
// Instructor:       deppeler
//
// Author:           Tom Tan
// Email:            ztan64@wisc.edu
// CS Login:         ttan
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          None
//
// Online sources:   None
//////////////////////////// 80 columns wide ///////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{

	// Check if number of command-line arguments is correct.
	// exit 1 if number of CLAs is not 5
	if (argc != 5)
	{
		printf("Usage: ./sequence n x0 m b\n");
		exit(1);
	}

	// extract the CLAs using atoi command
	int n = atoi(*(argv + 1));
	int x0 = atoi(*(argv + 2));
	int m = atoi(*(argv + 3));
	int b = atoi(*(argv + 4));

	for (int i = 1; i <= n; i++)
	{
		printf("%i", x0);

		// calculate the next x0 base on the rule
		x0 = (m * x0 + b);

		// not print "," at the end
		if (i != n)
		{
			printf(",");
		}
	}

	return 0;
}
