#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("Setting a 3-second alarm...\n");
    alarm(3);        // Request alarm signal after 3 seconds
    printf("Sleeping...\n");
    // This sleep may be interrupted by alarm 
    unsigned int left = sleep(10);
    printf("Sleep returned, %u seconds left.\n", left);
    return 0;
}
