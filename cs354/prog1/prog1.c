/* title: First C Program
 * file: prog1.c
 * author: Jim Skrentny
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    // Create space to save string of characters
    char * input_string = malloc(128);

    // INPUT: prompt user for input
    printf("Enter your CS login: ");

    // INPUT: read keyboard input into input_string variable
    if ( fgets(input_string, 50, stdin) == NULL ) {
    fprintf(stderr, "Error reading user input.\n");
    }

    // Replace ‘\n’ with ‘\0’
    int len = strlen(input_string);
    if ( input_string[len - 1] == '\n' ) {
        input_string[len - 1] = '\0';
    }

    // OUTPUT: print CS login to terminal
    printf("Your login: %s\n", input_string);

    return 0;
}