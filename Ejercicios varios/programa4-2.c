#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
   pid_t pid;
   int j, estado;


   for (j = 0; j < 10; j++)
   {
      pid = fork();
      if(pid == 0)
      {
         printf("El padre del proceso %d es %d, j = %d\n", getpid(), getppid(), j);
         		sleep(10);
		exit(0);
      }
   }

   for(int i=0; i<10; i++)
      wait(&estado);
   sleep(10);
}

