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
// Main File:        check_board.c
// This File:        check_board.c
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

char *DELIM = ",";  // commas ',' are a common delimiter character for data strings

/* COMPLETED (DO NOT EDIT):       
 * Read the first line of input file to get the size of that board.
 * 
 * PRE-CONDITION #1: file exists
 * PRE-CONDITION #2: first line of file contains valid non-zero integer value
 *
 * fptr: file pointer for the board's input file
 * size: a pointer to an int to store the size
 *
 * POST-CONDITION: the integer whos address is passed in as size (int *) 
 * will now have the size (number of rows and cols) of the board being checked.
 */
void get_board_size(FILE *fptr, int *size) {      
	char *line1 = NULL;
	size_t len = 0;

	if ( getline(&line1, &len, fptr) == -1 ) {
		printf("Error reading the input file.\n");
		free(line1);
		exit(1);
	}

	char *size_chars = NULL;
	size_chars = strtok(line1, DELIM);
	*size = atoi(size_chars);

	// free memory allocated for reading first link of file
	free(line1);
	line1 = NULL;
}

/* 
 * Returns 1 if and only if the board is in a valid Sudoku board state.
 * Otherwise returns 0.
 * 
 * A valid row or column contains only blanks or the digits 1-size, 
 * with no duplicate digits, where size is the value 1 to 9.
 * 
 * Note: p2A requires only that each row and each column are valid.
 * 
 * board: heap allocated 2D array of integers 
 * size:  number of rows and columns in the board
 */
int valid_board(int **board, int size) {
	// check if size is within 1-9, return 0 if violated
	if (size < 1 || size > 9)
	{
		return 0;
	}

	// outer loop to loop through all row
	for (int i = 0; i < size; i++)
	{
		// inner loop to loop through all column
		for (int j = 0; j < size; j++)
		{
			// check each number is within 1-size, return 0 if violated
			if (*(*(board + i) + j) < 0 || *(*(board + i) + j) > size)
			{
				return 0;
			}

			// only check the number if is not 0
			if (*(*(board + i) + j) != 0)
			{
				// check elements after the current element at the same row for duplicates
				for (int row = 1; row < (size - i); row++)
				{
					if (*(*(board + i) + j) == *(*(board + i + row) + j))
					{
						// if row duplicates found return 0
						return 0;
					}
				}

				// check elements at the same lower column for duplicates
				for (int column = 1; column < (size - j); column++)
				{
					if (*(*(board + i) + j) == *(*(board + i) + j + column))
					{
						// if column duplicates found return 0
						return 0;
					}
				}
			}
		}
	}

	return 1;
}    

/* 
 * This program prints "valid" (without quotes) if the input file contains
 * a valid state of a Sudoku puzzle board wrt to rows and columns only.
 *
 * A single CLA is required, which is the name of the file 
 * that contains board data is required.
 *
 * argc: the number of command line args (CLAs)
 * argv: the CLA strings, includes the program name
 *
 * Returns 0 if able to correctly output valid or invalid.
 * Only exit with a non-zero result if unable to open and read the file given.
 */
int main( int argc, char **argv ) {              

	// Check if number of command-line arguments is correct.
	// exit 1 if number of CLAs is not 2
	if (argc != 2) {
		printf("Usage: ./check_board <input_filename>\n");
		exit(1);
	}

	// Open the file and check if it opened successfully.
	FILE *fp = fopen(*(argv + 1), "r");
	if (fp == NULL) {
		printf("Can't open file for reading.\n");
		exit(1);
	}

	// Declare local variables.
	int size;

	// Call get_board_size to read first line of file as the board size.
	get_board_size(fp, &size);
	
	// Dynamically allocate a 2D array for given board size.
	// allocate a 1D array of integer pointers
	int **array = malloc(size * sizeof(int *));
	// check allocation
	if (array == NULL) {
		printf("unable to allocate memory.\n");
		exit(1);
	}
	// allocate for each row, a 1D array of integers with the size of the board
	for (int row = 0; row < size; row++) {
		*(array + row) = malloc(size * sizeof(int));
		// check allocation
		if (*(array + row) == NULL) {
			printf("unable to allocate memory.\n");
			exit(1);
		}
	}

	// Read the rest of the file line by line.
	// Tokenize each line wrt the delimiter character 
	// and store the values in your 2D array.
	char *line = NULL;
	size_t len = 0;
	char *token = NULL;
	for (int i = 0; i < size; i++) {

		if (getline(&line, &len, fp) == -1) {
			printf("Error while reading line %i of the file.\n", i+2);
			exit(1);
		}

		token = strtok(line, DELIM);
		for (int j = 0; j < size; j++) {
			// Complete the line of code below to initialize your 2D array.
			*(*(array + i) + j) = atoi(token);
			
			token = strtok(NULL, DELIM);
		}
	}

	// Call the function valid_board and print the appropriate
	// output depending on the function's return value.
	if (valid_board(array, size) == 1) {
		printf("valid\n");
	} else {
		printf("invalid\n");
	}

	// Free all dynamically allocated memory.
	// free inner layer of the 2D array
	for (int i = 0; i < size; i++) {
		free(*(array + i));
		*(array + i) = NULL;
	}
	// free outer 1D array of pointers
	free(array);
	array = NULL;
	// free line + token
	free(token);
	free(line);

	// Close the file.
	if (fclose(fp) != 0) {
		printf("Error while closing the file.\n");
		exit(1);
	} 

	return 0;       
}
