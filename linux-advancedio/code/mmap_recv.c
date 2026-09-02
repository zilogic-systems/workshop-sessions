# include <stdio.h>
# include <sys/types.h>
# include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  int fd;
  char * ptr,*base;
  fd=open("mymap.txt",O_RDWR);
  if(fd<0){
    perror("Couldn't open test.txt");
    return -1;
  }
  ptr=mmap(0,100,PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
  
  close(fd);
  
  if(ptr<0){
    perror("MMAP failed");
    return -1;
  }
  base=ptr;
  
  while(*ptr != '\0'){
    printf("%c",*ptr);
    ptr++;
  }
  
  *base='*';  

  munmap(base,100);
    
}
