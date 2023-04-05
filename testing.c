#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(void)
{

    printf("%s\n", strerror(errno));




    return 0;
}