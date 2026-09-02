#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("Simulating a fatal error using abort()...\n");
    abort();   // Sends abort signal to itself
    printf("This will never execute.\n");
    return 0;
}
