#include<stdio.h>

int main(void){
	int primero, intermedio, resultado;

	printf("Soy el proceso %d\n", getpid());
	intermedio = primero + 4 * 5 - 2;
	resultado = intermedio * 4;
	printf("%d\n", resultado);
	pause();
}