#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pid_t pid;
int counter = 0;

void tratar_alarma()
{
   counter = counter + 1;
   kill(getpid()+1, SIGKILL);
   printf("\nSe ejecuto correctamenta la señal\n");
}

int main(int argc, char *argv[])
{
   int pid, status;

   struct sigaction act;
   sigset_t mask;

   sigfillset(&mask);
   sigdelset(&mask, SIGTSTP);


   act.sa_handler = (void*)tratar_alarma;
   act.sa_flags = 0;

   sigprocmask(SIG_SETMASK, &mask, NULL);
   sigaction(SIGTSTP , &act, NULL);

   pid = fork();
   switch(pid)
   {
      case -1:
         exit(-1);

      case 0:
         sleep(15);
         exit(0);

      default:
         wait(&status);
         if (counter == 0)
         {
            kill(getpid()+1, SIGKILL);
            printf("El proceso hijo no ejecuto nada por lo que el padre lo termina\n");
            sleep(15);
         }
         else
         {
            printf("El proceso hijo se elimino a el mismo\n");
            sleep(15);
         }
   }
   exit(0);
}
   


