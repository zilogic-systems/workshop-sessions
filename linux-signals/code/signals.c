#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <getopt.h>

void handler()
{
  fprintf(stderr,"I am in handler of SIGINT\n");
  return ;
}


int main(int argc,char * argv[])
{

  signal(SIGINT,handler);
  pause();
  return 0;
}
    





