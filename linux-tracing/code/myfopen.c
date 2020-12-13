#include <stdio.h>

FILE *fopen(const char *path, const char *mode)
{
    printf("Always failing fopen\n");
    return NULL;
}
