#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

struct var
   {
      char Nombre[10];
      int Edad;
      float promedio;
   };


void *funcion(void *var1)
{
   struct var *aux = (struct var*)var1;
   printf("El hilo hijo imprime los datos dentro del struct:\n");
   printf("Mi nombre es : %s\n", (*aux).Nombre);
   printf("Mi edad es : %i\n", (*aux).Edad);
   printf("Mi promedio es : %.2f\n", (*aux).promedio);
   printf("El hilo hijo termina\n");
}



int main(void)
{
   struct var var1;

   strcpy(var1.Nombre, "Enrique");
   var1.Edad = 23;
   var1.promedio = 7.63;

   pthread_t th1;
   pthread_create(&th1, NULL, (void *)funcion, (void *) &var1);
   pthread_join(th1, NULL);

   printf("El hilo principal termina\n");
   
   exit(0);
}

