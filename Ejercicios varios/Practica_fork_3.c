#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <sys/mman.h>


int main()
{

   int estado;
   long double deltaX, mid, Xm = 1, N,suma1=0, suma2 = 0, sumaR;
   pid_t pid;


   printf("Ingrese el valor de Delta X: (Menor que 1)\n");
   scanf("%Lf", &deltaX);


   N = Xm/deltaX;
   deltaX = Xm/N;
   mid = deltaX/2;

   pid = fork();
   if(pid == 0)
   {
      for(int i = 1; i < N; i = i + 2)
      {
         long double altura;
         altura = sqrtl(1-powl(((i*deltaX) + mid), 2));

         suma1 = suma1 + (deltaX*altura);
         
      }
      suma1 = suma1*4;
      printf("Suma 1: %.50Lf\n", suma1);
	exit(0);
   }
   else
   {

      for(int i = 0; i < N; i = i + 2)
      {
         long double altura;
         altura = sqrtl(1-powl(((i*deltaX) + mid), 2));

         suma2 = suma2 + (deltaX*altura);

      }
      suma2 = suma2*4;
	printf("Suma 2: %.50Lf\n", suma2);
      sleep(10);

   }
   exit(0);
   
}

