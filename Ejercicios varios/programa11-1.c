#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void tratar_alarma(void)
{
   printf("Alarma activada con numero de señal: %d\n", SI_KERNEL);
}

void tratar_SIGTSTP(void)
{
   printf("Me han intentado detener\n");
}

int main(void)
{
   struct sigaction act;
   sigset_t mask;

   sigfillset(&mask);
   sigdelset(&mask, SIGALRM);

   /* especifica el manejador */
   act.sa_handler = (void *)tratar_alarma; /*funcion a ejecutar */
   act.sa_flags = 0; /* Ninguna accion especifica */
   
   sigprocmask(SIG_SETMASK, &mask, NULL);
   sigaction(SIGALRM, &act, NULL);

   for(;;)
   {
      alarm(3);
      pause(); /* se suspende el proceso hasta que se reciba la señal */
   }
}

