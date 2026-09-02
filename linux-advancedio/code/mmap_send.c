# include <stdio.h>
# include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int main()
{
  int fd;
  char * ptr,*base;
  int i=0;

    fd=open("mymap.txt",O_RDWR|O_CREAT|O_TRUNC,S_IRWXU|S_IRWXG);
  
  
if(fd<0){
    perror("Couldn't open test.txt");
    return -1;
  }
  
  lseek(fd,100,SEEK_SET); 
  write(fd," ",1);
  lseek(fd,0,SEEK_SET);
  ptr=mmap(0,100,PROT_WRITE,MAP_SHARED,fd,0);

  close(fd);
  if(ptr<0){
    perror("MMAP failed");
    return -1;
  }

  
  base=ptr;

  for(i=0;i<26;i++)
    *(ptr+i)='a'+i;
 
  *(ptr+i)='\0';
  #if 0
  printf("Waiting");
  while(*ptr!='*'){
    sleep(1); 
    printf(".");
  }
  #endif

  munmap(base,100);
  
}
