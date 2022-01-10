#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define FALSE 0
#define TRUE 1
#define NUM 2

int turno, interesado[NUM];

void entrar_region(int proceso)
{
   int otro;

   otro = 1 - proceso;
   interesado[proceso] = TRUE;
   turno = proceso;
   while(turno == proceso && interesado[otro] == TRUE);
}

void salir_region(int proceso)
{
   interesado[proceso] = FALSE;
}


int main(int argc, char *argv[])
{
   int shmid, N = 0, estado;
   int *variable;
   pid_t pid;

   printf("Ingrese el valor de N\n");
   scanf("%d", &N);


   key_t llave;
   llave = ftok(argv[0], 'K');
   if((shmid = shmget(llave, sizeof(int), IPC_CREAT | 0600)) == -1)
   {
      perror("Error en shmget");
      exit(-1);
   }
   /* Nos atamos a la memoria compartida */
   if((variable = (int *)shmat(shmid, NULL, 0)) == (int *)(-1))
   {
      perror("Fallo shmat");
      exit(-1);
   }

   *variable = 0;

   pid = fork();

   if (pid == -1)
   {
      perror("Error en el fork");
   }

   else if(pid == 0)
   {
      for (int i = 0; i < N; ++i)
      {
         entrar_region(0);
         *variable = *variable - 1;
         salir_region(0);
      }
      exit(0);
   }

   else
   {
      for (int i = 0; i < N; ++i)
      {
         entrar_region(1);
         *variable = *variable + 1;
         salir_region(1);
      }
   }

   wait(&estado)

   printf("La variable tiene el valor final de:%d\n", *variable);

   shmctl(shmid, IPC_RMID, 0);
   exit(0);
}
