///////////////////////////////////////////////////////////////////////////////
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Spring 2022, Deb Deppeler
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2021 Deb Deppeler
// Posting or sharing this file is prohibited, including any changes/additions.
//
// We have provided comments and structure for this program to help you get
// started.  Later programs will not provide the same level of commenting,
// rather you will be expected to add same level of comments to your work.
// 09/20/2021 Revised to free memory allocated in get_board_size function.
// 01/24/2022 Revised to use pointers for CLAs
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        myMagicSquare.c
// This File:        myMagicSquare.c
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

// Structure that represents a magic square
typedef struct
{
    int size;           // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/*
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize()
{
    fprintf(stdout, "Enter magic square's size (odd integer >=3)\n");

    int size;

    // read from stdin, check if EOF, write the result to size
    if (scanf("%i", &size) == EOF)
    {
        fprintf(stderr, "Input error!\n");
        exit(1);
    }

    // check if inputsize is odd
    if (size % 2 == 0)
    {
        fprintf(stdout, "Magic square size must be odd.\n");
        exit(0);
    }

    // check if inputsize >= 3
    if (size < 3)
    {
        fprintf(stdout, "Magic square size must be >= 3.\n");
        exit(0);
    }

    return size;
}

/*
 * Makes a magic square of size n using the
 * Siamese magic square algorithm or alternate from assignment
 * or another valid alorithm that produces a magic square.
 *
 * n is the number of rows and columns
 *
 * returns a pointer to the completed MagicSquare struct.
 */
MagicSquare *generateMagicSquare(int n)
{
    // allocate memory for the MagicSquare struct
    MagicSquare *magicSquareReturn = malloc(sizeof(MagicSquare));
    // check for valid allocation
    if (magicSquareReturn == NULL)
    {
        fprintf(stderr, "unable to allocate memory.\n");
        exit(1);
    }
    // set size of the magic square
    magicSquareReturn->size = n;

    // allocate a 1D array of integer pointers
    magicSquareReturn->magic_square = malloc(n * sizeof(int *));
    // check for valid allocation
    if (magicSquareReturn->magic_square == NULL)
    {
        fprintf(stderr, "unable to allocate memory.\n");
        exit(1);
    }

    // allocate the inner 1D array of integers
    for (int i = 0; i < n; i++)
    {
        *(magicSquareReturn->magic_square + i) = malloc(n * sizeof(int));
        // check for valid allocation
        if (*(magicSquareReturn->magic_square + i) == NULL)
        {
            fprintf(stderr, "unable to allocate memory.\n");
            exit(1);
        }
    }

    // set all array value to 0, can be swapped by using calloc
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            *(*(magicSquareReturn->magic_square + i) + j) = 0;
        }
    }

    // starting filling sequence at the middle of the first row
    int startRow = 0;
    int startCol = n / 2;
    for (int i = 1; i <= n * n; i++)
    {
        // write sequence number to the current location
        *(*(magicSquareReturn->magic_square + startRow) + startCol) = i;

        // save the original location in case we need to move it down one row
        int originalRow = startRow;
        int originalCol = startCol;

        // calculate the location index if we move it diagonally up and right
        // when at the edge, wrap around to the other side
        if (startRow == 0)
        {
            startRow = n - 1;
        }
        else
        {
            startRow--;
        }
        if (startCol == n - 1)
        {
            startCol = 0;
        }
        else
        {
            startCol++;
        }

        // if the calculated location is already occupied (!= 0)
        // continue set next position one row from the original location
        while (i != n * n && *(*(magicSquareReturn->magic_square + startRow) + startCol) != 0)
        {
            startRow = originalRow + 1;
            startCol = originalCol;
        }
    }

    return magicSquareReturn;
}

/*
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename)
{
    // open the file in write mode
    FILE *fp = fopen(filename, "w");
    // check if we can open/create the file
    if (fp == NULL)
    {
        fprintf(stderr, "unable to open file.\n");
        exit(1);
    }

    // write size of the magic square first
    fprintf(fp, "%i\n", magic_square->size);

    // write the magic square in specified format
    for (int col = 0; col < magic_square->size; col++)
    {
        for (int row = magic_square->size - 1; row >= 0; row--)
        {
            // write the magic_square element
            fprintf(fp, "%i", *(*(magic_square->magic_square + row) + col));
            // only print comma if it's not the last element
            if (row != 0)
            {
                fprintf(fp, ",");
            }
        }

        // avoid printing a new line at the end
        if (col != magic_square->size - 1)
        {
            fprintf(fp, "\n");
        }
    }

    // Close the file, check fclose().
    if (fclose(fp) != 0)
    {
        fprintf(stderr, "Error while closing the file.\n");
        exit(1);
    }
}

/*
 * Generates a magic square of the user specified size and
 * outputs the square to the output filename.
 *
 * Add description of required CLAs here
 */
int main(int argc, char **argv)
{
    // Check input arguments to get output filename
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./myMagicSquare <output_filename>\n");
        exit(1);
    }

    // Get magic square's size from user
    int size = getSize();

    //       Generate the magic square by correctly interpreting
    //       the algorithm(s) in the write-up or by writing or your own.
    //       You must confirm that your program produces a
    //       Magic Sqare as described in the linked Wikipedia page.

    // receive the magic square heap address from generateMagicSquare()
    MagicSquare *magicSquare = generateMagicSquare(size);

    // Output the magic square
    fileOutputMagicSquare(magicSquare, *(argv + 1));

    // Free the inner 1D array of integers memory
    for (int i = 0; i < magicSquare->size; i++)
    {
        free(*(magicSquare->magic_square + i));
        *(magicSquare->magic_square + i) = NULL;
    }
    // Free the outer 1D array of integer pointers
    free(magicSquare->magic_square);
    magicSquare->magic_square = NULL;

    // Free the MagicSquare struct pointer
    free(magicSquare);
    magicSquare = NULL;

    return 0;
}

// S23
