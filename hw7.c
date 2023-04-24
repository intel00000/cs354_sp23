#include <stdio.h>
#include <string.h>

typedef union
{
    double d;
    char c[20];
} U;

struct st1
{
    char c[19];
    short s;
};
struct st2
{
    int i[3];
    char c[8];
    short s[1];
};
struct st3
{
    char c[5];
    int i[2];
    short s[3];
};

int main()
{
    U temp;
    temp.d = 11.5;
    strcpy(temp.c, "CS 354");
    printf("%zu, %f,  %s\n", sizeof(temp), temp.d, temp.c);

    struct st1 s1;
    struct st2 s2;
    struct st3 s3;

    // printf each struct size
    printf("%zu, %zu, %zu\n", sizeof(s1), sizeof(s2), sizeof(s3));

    char myArray[4][8];

    // print the size of the array
    printf("%p, %p\n", &myArray[0][1], &myArray[0][0]);
    printf("%d\n", &myArray[2][5] - &myArray[0][0]);

    char *myArray3D[5][10][15];

    // print the size of the array
    printf("%p, %p\n", &myArray3D[0][0][1], &myArray3D[0][0][0]);
    printf("%d\n", &myArray3D[3][4][5] - &myArray3D[0][0][0]);

    return 0;
}