#include <stdio.h>
#include <unistd.h>

int main(void)
{
    fork();   // one call, but it creates a child

    printf("Hello, I am a process!\n");

    return 0;
}
