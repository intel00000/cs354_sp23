#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data
{
    int n;
    char *name;
    int *arr[3];
};

int main()
{
    struct Data *sptr = malloc(sizeof(struct Data));
    sptr->n = 33;
    sptr->name = malloc(12 * sizeof(char));
    if (sptr->name == NULL)
    {
        printf("Unable to allocate memory.\n");
        exit(1);
    }
    for (int i = 0; i < 3; i++)
    {
        sptr->arr[i] = malloc(4 * sizeof(int));
        if (sptr->arr[i] == NULL)
        {
            printf("Unable to allocate memory.\n");
            exit(1);
        }
        for (int j = 0; j < 4; j++)
            *(sptr->arr[i] + j) = 0;
    }

    for (int i = 0; i < 3; i++)
    {
        sptr->arr[i] = malloc(2 * sizeof(int));
        if (sptr->arr[i] == NULL)
        {
            printf("Unable to allocate memory.\n");
            exit(1);
        }
        for (int j = 0; j < 2; j++)
            *(sptr->arr[i] + j) = 0;
    }
    for (int i = 0; i < 3; i++)
    {
        sptr->arr[i] = realloc(sptr->arr[i], 4 * sizeof(int));
        if (sptr->arr[i] == NULL)
        {
            printf("Unable to allocate memory.\n");
            exit(1);
        }
        for (int j = 0; j < 2; j++)
            *(sptr->arr[i] + j + 2) = 0;
    }

    return 0;
}