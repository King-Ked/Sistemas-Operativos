#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
   pid_t pid;
   int i = 0, estado;
   pid = fork();
   if(pid == -1) /* error del fork */
   {
          perror("Error en el fork");
   }

   else if (pid == 0) /* proceso hijo */
   {
      sleep(5);
      printf("Soy el hijo: PID %d; PPID = %d i = %d\n", getpid(), getppid(), ++i);
      exit(0);
   }

   else
   {
      printf("Soy el padre: PID %d; PPID = %d i = %d\n", getpid(), getppid(), --i);
      exit(0);
   }
   
   sleep(20);
}

