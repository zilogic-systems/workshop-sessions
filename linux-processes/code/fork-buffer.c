#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Hello");
    
    fork(); 

    return 0;
}
