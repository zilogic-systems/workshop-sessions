# include <stdio.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/sem.h>
# include <stdlib.h> 

#define SEMPOST 1 
#define SEMWAIT -1

 union semun {
               int val;
               struct semid_ds *buf;
               ushort *array;
          };

main()
{ 
  int i,j; 
  int pid;
  int semid; /* semid of semaphore set */
  key_t key = 1234; /* key to pass to semget() */
  int semflg = IPC_CREAT | 0666; /* semflg to pass to semget() */
  int nsems = 1; /* nsems to pass to semget() */
  int nsops; /* number of operations to do */
  int semstat=0;
  int cnt=0;
  struct sembuf *sops = (struct sembuf *) malloc(2*sizeof(struct sembuf)); 
  /* ptr to operations to perform */

  /* set up semaphore */

   if ((semid = semget(key, nsems, semflg)) == -1) {
	perror("semget: semget failed");
	exit(1);
      } else 
	(void) fprintf(stderr, "semget: semget succeeded: semid =\
%d\n", semid);

   i = semctl(semid,0,SETVAL, 1);
   if (i == -1) {
     perror("semctl: semctl failed");
     exit(1);
   }

  if((pid=fork())<0){
    perror("Fork failure");
    return -1;

  }else if(pid==0)    {

    while(cnt<2){
      cnt++;
      sops[0].sem_num=0;
      sops[0].sem_op=SEMWAIT;
      sops[0].sem_flg=SEM_UNDO;

      printf("Lets fetch semaphore\n");
      if(semstat=semop(semid,sops,1)==-1){
	perror("semop failed");
      }
      
      printf("got the semaphore\n");

      sleep(10);

      sops[0].sem_num=0;
      sops[0].sem_op=SEMPOST;
      sops[0].sem_flg=SEM_UNDO;

      printf("Lets leave semaphore\n");
      if(semstat=semop(semid,sops,1)==-1){
	perror("semop failed");
      }
      
      printf("released the semaphore\n");
    }
    
  } else if(pid>0){

    cnt=0;
    while (cnt<2) {
      cnt++;
      sops[0].sem_num=0;
      sops[0].sem_op=SEMWAIT;
      sops[0].sem_flg=SEM_UNDO;

      sleep(2);
      printf("parent:Lets fetch semaphore\n");
      if(semstat=semop(semid,sops,1)==-1){
	perror("semop failed");
      }
      
      printf("Parent:got the semaphore\n");

      sleep(10);

      sops[0].sem_num=0;
      sops[0].sem_op=SEMPOST;
      sops[0].sem_flg=SEM_UNDO;

      printf("parent:Lets leave semaphore\n");
      if(semstat=semop(semid,sops,1)==-1){
	perror("semop failed");
      }
      
      printf("parent:released the semaphore\n");
    }
  }
}

    
