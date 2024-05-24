////////////////////////////////////////////////////////////////////////////////
// Main File:        simple_sequence.c
// This File:        simple_sequence.c
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

int main(void) {
        for (int i = 1; i < 11; i++) {
                printf("%i", i);

                if (i != 10) {
                        printf(",");
                }
        }

        printf("\n");

        return 0;
}