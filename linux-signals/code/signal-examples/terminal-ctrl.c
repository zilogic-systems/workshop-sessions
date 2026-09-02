// ctrl_c_demo.c
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int i = 0;
    printf("PID = %d\n", getpid());
    printf("Try pressing Ctrl-C or Ctrl-Z in this terminal.\n");

    while (1) {
        printf("Working... i = %d\n", i++);
        sleep(1);
    }

    return 0;
}
