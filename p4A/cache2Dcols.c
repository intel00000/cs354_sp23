///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020-2023 Deb Deppeler based on work by Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission SPRING 2023, CS354-deppeler
//
///////////////////////////////////////////////////////////////////////////////
// Main File:        cache2Dcols.c
// This File:        cache2Dcols.c
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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define GLOBAL_N 10

// declare 2D global stack allocated array of dimensions 3000 rows x 500 columns
int arr2D[3000][500];

/*
 * This function is used to measure the time it takes to access a 2D array elements in column-wise order.
 */
int main(void)
{
    // an inner loop iterate through rows, outer loop iterate through columns of the array
    for (int col = 0; col < 500; col++)
    {
        for (int row = 0; row < 3000; row++)
        {
            arr2D[row][col] = row + col;
        }
    }

    return 0;
}