#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("El programa se debe ejecutar como: %s archivo\n", argv[0]);
		exit(-1);
	}
	FILE * flujo = fopen(argv[1], "rb");
	if (flujo == NULL)
	{
		perror("Error en la apertura del archivo");
		return 1;
	}

	char caracter;

	while(feof(flujo)==0)
	{
		caracter = fgetc(flujo);
		printf("%c", caracter);
	}

	fclose(flujo);
	printf("\n\nTermino el archivo\n");

	return 0;
}
