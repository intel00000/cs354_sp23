#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(void)
{
    // set errno flag
    errno = ENOENT;

    printf("%s\n", strerror(errno));

    return 0;
}