#include <stdio.h>

static int z = 1;
extern int a;

int addition(int x, int y)
{
        return x + y;
}

int main()
{
        static int ab = 0;
        static int abc = 1;


        abc = 2;
        a = 5;
        z = 1;
        return 0;
}
