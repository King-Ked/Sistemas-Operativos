#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <semaphore.h>
#include <fcntl.h>
#include <signal.h>
#include <strings.h>


struct registro_EMPLEADO
{
   char INIC[2];
   char ID[7];
   char salario[6];
};

long i = 0;

sem_t mutex1;
sem_t mutex2;
sem_t mutex3;
sem_t mutex4;
sem_t mutex5;

void Hilo1(void *FILE);
void Hilo2(void *FILE);
void Hilo3(void *FILE);
void Hilo4(void *FILE);

int main(void)
{

   long int suma = 0;
   int j = 0, opt, aux_ID, aux_salario;
   char aux_INIC, letra;


   FILE *flujo = fopen("empleados", "rb");
   if (flujo == NULL)
   {
      perror("Error en la apertura del archivo");
      return 1;
   }

   FILE *flujo1 = fopen("empleados", "rb");
   if (flujo1 == NULL)
   {
      perror("Error en la apertura del archivo");
      return 1;
   }

   pthread_t th1, th2, th3, th4;

   sem_init(&mutex1, 0, 4);
   sem_init(&mutex2, 0, 3);
   sem_init(&mutex3, 0, 2);
   sem_init(&mutex4, 0, 1);
   sem_init(&mutex5, 0, 0);

   pthread_create(&th1, NULL, (void *)Hilo1, (void*)&flujo);
   pthread_create(&th2, NULL, (void *)Hilo2, (void*)&flujo);
   pthread_create(&th3, NULL, (void *)Hilo3, (void*)&flujo);
   pthread_create(&th4, NULL, (void *)Hilo4, (void*)&flujo);

   do
   {
      printf("\nPresione la tecla para ver la informacion correspondiente:\n");
      printf("\nVisualizar el numero de transacciones hasta el momento\t\t\t 1\n");
      printf("\nVisualizar el numero de registros cuyo campo INIC es la letra...\t 2\n");
      printf("\nObtener la suma del salario de todos los registros\t\t\t 3\n");
      printf("\nFinalizar\t\t\t\t\t\t\t\t 4\n");

      scanf("%d", &opt);

      switch(opt)
      {
         case 1:
            printf("\nSe han realizado %ld transacciones hasta el momento\n", i);
            break;

         case 2:
            printf("Ingrese la letra que desea buscar (Mayuscula)\n");
            scanf(" %c", &letra);
            sem_wait(&mutex5);
            while(feof(flujo1) == 0)
            {
               fscanf(flujo1, "%c%6d", &aux_INIC, &aux_ID);
               if (letra == aux_INIC)
               {
                  printf("ID: %d\n", aux_ID);   
               }
            }
            rewind(flujo1);
            break;

         case 3:
            sem_wait(&mutex5);
            while(feof(flujo1) == 0)
            {
               fscanf(flujo1, "%c%d%d", &aux_INIC, &aux_ID, &aux_salario);
               suma = suma + aux_salario;
            }
            printf("El valor de la suma es: %ld\n", suma);
            suma = 0;
            rewind(flujo1);
            usleep(50);
            break;

         case 4:
            sem_wait(&mutex5);
            j++;
            break;

      }
   } while(j == 0);

   exit(0);
}

void Hilo1(void *flujo)
{
   for(;;)
   {
      sem_wait(&mutex5);
      int rest_ID, sum_ID, fd_destino;
      int aux_ID, aux_salario;
      char aux_INIC;
      struct registro_EMPLEADO aux_registro;
      remove("aux_empleado");

      if((fd_destino = open("aux_empleado", O_WRONLY|O_TRUNC|O_CREAT, 0666)) == -1)
      {
         perror("aux_empleado");
         exit(-1);
      }
      bzero((char *)(&aux_registro), sizeof(aux_registro));

      rest_ID = (rand()%100000) + 1;
      sum_ID = (rand()%100000) + 1;

      while(feof(*((FILE **)flujo)) == 0)
      {
         fscanf((*((FILE **)flujo)), "%c%d%d", &aux_INIC, &aux_ID, &aux_salario);
         
         if(rest_ID == aux_ID)
         {
            sprintf(aux_registro.INIC, "%c ", aux_INIC);
            sprintf(aux_registro.ID, "%.6d ", aux_ID);
            sprintf(aux_registro.salario, "%d ", aux_salario - 1);
            write(fd_destino, &aux_registro, 0);
            write(fd_destino, "\n", 2);
         }
         else if(sum_ID == aux_ID)
         {
            sprintf(aux_registro.INIC, "%c ", aux_INIC);
            sprintf(aux_registro.ID, "%.6d ", aux_ID);
            sprintf(aux_registro.salario, "%d ", aux_salario + 1);
            write(fd_destino, &aux_registro, sizeof(struct registro_EMPLEADO));
            write(fd_destino, "\n", 2);
            
         }
         else
         {
            sprintf(aux_registro.INIC, "%c ", aux_INIC);
            sprintf(aux_registro.ID, "%.6d ", aux_ID);
            sprintf(aux_registro.salario, "%d ", aux_salario);
            write(fd_destino, &aux_registro, sizeof(struct registro_EMPLEADO));
            write(fd_destino, "\n", 2);
         }
      }
      rewind(*((FILE **)flujo));
      sem_post(&mutex4);
      sem_post(&mutex1);
      i++;
   }

}

void Hilo2(void *flujo)
{
   for(;;)
   {
      sem_wait(&mutex4);
      int rest_ID, sum_ID, fd_destino;
      int aux_ID, aux_salario;
      char aux_INIC;
      struct registro_EMPLEADO aux_registro;
      remove("aux_empleado");

      if((fd_destino = open("aux_empleado", O_WRONLY|O_TRUNC|O_CREAT, 0666)) == -1)
      {
         perror("aux_empleado");
         exit(-1);
      }
      bzero((char *)(&aux_registro), sizeof(aux_registro));

      rest_ID = (rand()%100000) + 1;
      sum_ID = (rand()%100000) + 1;

      while(feof(*((FILE **)flujo)) == 0)
      {
         fscanf((*((FILE **)flujo)), "%c%d%d", &aux_INIC, &aux_ID, &aux_salario);
         
         if(rest_ID == aux_ID)
         {
            sprintf(aux_registro.INIC, "%c ", aux_INIC);
            sprintf(aux_registro.ID, "%.6d ", aux_ID);
            sprintf(aux_registro.salario, "%d ", aux_salario - 1);
            write(fd_destino, &aux_registro, sizeof(struct registro_EMPLEADO));
            write(fd_destino, "\n", 2);
         }
         else if(sum_ID == aux_ID)
         {
            sprintf(aux_registro.INIC, "%c ", aux_INIC);
            sprintf(aux_registro.ID, "%.6d ", aux_ID);
            sprintf(aux_registro.salario, "%d ", aux_salario + 1);
            write(fd_destino, &aux_registro, sizeof(struct registro_EMPLEADO));
            write(fd_destino, "\n", 2);
         }
         else
         {
            sprintf(aux_registro.INIC, "%c ", aux_INIC);
            sprintf(aux_registro.ID, "%.6d ", aux_ID);
            sprintf(aux_registro.salario, "%d ", aux_salario);
            write(fd_destino, &aux_registro, sizeof(struct registro_EMPLEADO));
            write(fd_destino, "\n", 2);
         }
      }
      rewind(*((FILE **)flujo));
      sem_post(&mutex3);
      sem_post(&mutex1);
      i++;
   }

}

void Hilo3(void *flujo)
{
   for(;;)
   {
      sem_wait(&mutex3);
      int rest_ID, sum_ID, fd_destino;
      int aux_ID, aux_salario;
      char aux_INIC;
      struct registro_EMPLEADO aux_registro;
      remove("aux_empleado");

      if((fd_destino = open("aux_empleado", O_WRONLY|O_TRUNC|O_CREAT, 0666)) == -1)
      {
         perror("aux_empleado");
         exit(-1);
      }
      bzero((char *)(&aux_registro), sizeof(aux_registro));

      rest_ID = (rand()%100000) + 1;
      sum_ID = (rand()%100000) + 1;

      while(feof(*((FILE **)flujo)) == 0)
      {
         fscanf((*((FILE **)flujo)), "%c%d%d", &aux_INIC, &aux_ID, &aux_salario);
         
         if(rest_ID == aux_ID)
         {
            sprintf(aux_registro.INIC, "%c ", aux_INIC);
            sprintf(aux_registro.ID, "%.6d ", aux_ID);
            sprintf(aux_registro.salario, "%d ", aux_salario - 1);
            write(fd_destino, &aux_registro, sizeof(struct registro_EMPLEADO));
            write(fd_destino, "\n", 2);
         }
         else if(sum_ID == aux_ID)
         {
            sprintf(aux_registro.INIC, "%c ", aux_INIC);
            sprintf(aux_registro.ID, "%.6d ", aux_ID);
            sprintf(aux_registro.salario, "%d ", aux_salario + 1);
            write(fd_destino, &aux_registro, sizeof(struct registro_EMPLEADO));
            write(fd_destino, "\n", 2);
         }
         else
         {
            sprintf(aux_registro.INIC, "%c ", aux_INIC);
            sprintf(aux_registro.ID, "%.6d ", aux_ID);
            sprintf(aux_registro.salario, "%d ", aux_salario);
            write(fd_destino, &aux_registro, sizeof(struct registro_EMPLEADO));
            write(fd_destino, "\n", 2);
         }
      }
      rewind(*((FILE **)flujo));
      sem_post(&mutex2);
      sem_post(&mutex1);
      i++;
   }

}

void Hilo4(void *flujo)
{
   for(;;)
   {
      sem_wait(&mutex2);
      int rest_ID, sum_ID, fd_destino;
      int aux_ID, aux_salario;
      char aux_INIC;
      struct registro_EMPLEADO aux_registro;
      remove("aux_empleado");

      if((fd_destino = open("aux_empleado", O_WRONLY|O_TRUNC|O_CREAT, 0666)) == -1)
      {
         perror("aux_empleado");
         exit(-1);
      }
      bzero((char *)(&aux_registro), sizeof(aux_registro));

      rest_ID = (rand()%100000) + 1;
      sum_ID = (rand()%100000) + 1;

      while(feof(*((FILE **)flujo)) == 0)
      {
         fscanf((*((FILE **)flujo)), "%c%d%d", &aux_INIC, &aux_ID, &aux_salario);
         
         if(rest_ID == aux_ID)
         {
            sprintf(aux_registro.INIC, "%c ", aux_INIC);
            sprintf(aux_registro.ID, "%.6d ", aux_ID);
            sprintf(aux_registro.salario, "%d ", aux_salario - 1);
            write(fd_destino, &aux_registro, sizeof(struct registro_EMPLEADO));
            write(fd_destino, "\n", 2);
         }
         else if(sum_ID == aux_ID)
         {
            sprintf(aux_registro.INIC, "%c ", aux_INIC);
            sprintf(aux_registro.ID, "%.6d ", aux_ID);
            sprintf(aux_registro.salario, "%d ", aux_salario + 1);
            write(fd_destino, &aux_registro, sizeof(struct registro_EMPLEADO));
            write(fd_destino, "\n", 2);
         }
         else
         {
            sprintf(aux_registro.INIC, "%c ", aux_INIC);
            sprintf(aux_registro.ID, "%.6d ", aux_ID);
            sprintf(aux_registro.salario, "%d ", aux_salario);
            write(fd_destino, &aux_registro, sizeof(struct registro_EMPLEADO));
            write(fd_destino, "\n", 2);
         }
      }
      rewind(*((FILE **)flujo));
      sem_post(&mutex1);
      sem_post(&mutex5);
      i++;
   }

}