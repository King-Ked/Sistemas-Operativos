/* Programa para ilustrar el uso de semáforos */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEMAFORO_PADRE 2
#define SEMAFORO_HIJO1 0
#define SEMAFORO_HIJO2 1

int main(int argc, char *argv[])
{
   int semid, pid1, pid2, j = 10;
   struct sembuf operacion;
   key_t llave;

   llave = ftok(argv[0], 'U');
   if((semid = semget(llave, 3, IPC_CREAT | 0600)) == -1)
   {
      perror("Error al ejecutar semget");
      exit(-1);
   }
   semctl(semid, SEMAFORO_HIJO1, SETVAL, 0);
   semctl(semid, SEMAFORO_HIJO2, SETVAL, 1);
   semctl(semid, SEMAFORO_PADRE , SETVAL, 2);


   /* Se crea el proceso hijo */
   if((pid1 = fork()) == -1)
   {
      perror("Error al ejecutar fork");
      exit(-1);
   }
   else if (pid1 == 0)
   {
      /* Código correspondiente al proceso hijo1 */
      while(j)
      {
         /* Se realiza la operación DOWN en el semáforo del proceso hijo */
         operacion.sem_flg = 0;
         operacion.sem_op = -2;
         operacion.sem_num = SEMAFORO_HIJO1 ;
         semop(semid, &operacion, 1);
         printf("SOY EL PROCEsO HIJO1. IMPRESION: %d\n", j--);
         
         /* Se realiza la operación UP en el semáforo del proceso padre */
         
         operacion.sem_op = 2;
         operacion.sem_num = SEMAFORO_HIJO2;
         semop(semid, &operacion, 1);
      }
      
      /* Borramos el semáforo */
      semctl(semid, 0, IPC_RMID, 0);
   }
   else if((pid2 = fork()) == -1)
   {
      perror("Error al ejecutar fork");
      exit(-1);
   }
   else if(pid2 == 0)
   {
      /* Código correspondiente al proceso hijo2 */
      while(j)
      {
         /* Se realiza la operación DOWN en el semáforo del proceso hijo2 */
         operacion.sem_flg = 0;
         operacion.sem_op = -2;
         operacion.sem_num = SEMAFORO_HIJO2 ;
         semop(semid, &operacion, 1);
         printf("SOY EL PROCESO HIJO2. IMPRESION: %d\n", j--);
         
         /* Se realiza la operación UP en el semáforo del proceso padre */
         operacion.sem_op = 2;
         operacion.sem_num = SEMAFORO_PADRE;
         semop(semid, &operacion, 1);
         
      }
      
      /* Borramos el semáforo */
      semctl(semid, 0, IPC_RMID, 0);  
   }

   else
   {
   /* Código correspondiente al proceso padre */
      while(j)
      {
         /* Se realiza la operación DOWN en el semáforo del proceso padre */
         operacion.sem_flg = 0;
         operacion.sem_op = -2;
         operacion.sem_num = SEMAFORO_PADRE;
         semop(semid, &operacion, 1);
         printf("SOY EL PROCESO PADRE. IMPRESION: %d\n", j--);
         
         /*Se realiza la operación UP en el semáforo del proceso hijo */
         operacion.sem_op = 2;
         operacion.sem_num = SEMAFORO_HIJO1 ;
         semop(semid, &operacion, 1);


      }
      
      /* Borramos el semáforo */
      semctl(semid, 0, IPC_RMID, 0);
   }
}

