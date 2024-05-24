/* title: First C Program
 * file: prog1.c
 * author: Jim Skrentny
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

int power(int base, int n){
    int output = base;

    for (int i = 0; i < n; i++) {
        output = output * base;
    }

    return output;
}

int main() {
    int *a = malloc(sizeof(int) * 5);

    printf("testing start\n");
    *a = 123;
    printf("a[0]: %p\n", a);
    printf("a[1]: %p\n", ++a);
    printf("a[2]: %p\n", a+1);

    printf("a[0]: %i\n", *(a));

    printf("upper case lower case distance: %i\n", 'A' - 'a');
    
    if (1) {
        printf("power: %i\n", power(2, 2));
    }
    
    printf("testing end\n");

    char *sptr = "CS 354";
    char str[9] = "CS 354";


    strcpy(str, "formication");
    printf("str: %s\n", str);

    sptr = "mumpsimus";


    return 0;
}