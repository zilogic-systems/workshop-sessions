#include <stdio.h>

int main(void) {
    int a = 1, b = 0;

    printf("About to divide by zero...\n");
    int c = a / b;   // Triggers Floating Point Exception
    printf("Result: %d\n", c);

    return 0;
}
