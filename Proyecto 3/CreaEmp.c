#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

struct registro_EMPLEADO 
{
	char INIC[2];
	char ID[7];
	char salario[6];
};

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("El programa se debe ejecutar como: %s empleados\n", argv[0]);
		exit(-1);
	}
	remove(argv[1]);
	int i, fd_destino;
	struct registro_EMPLEADO registro;

	if((fd_destino = open(argv[1], O_WRONLY|O_TRUNC|O_CREAT, 0666)) == -1)
	{
		perror(argv[1]);
		exit(-1);
	}

	bzero((char *)(&registro), sizeof(registro));

	for(i = 1; i <= 100000; i++)
	{
		sprintf(registro.INIC, "%c ", ((rand()%26) + 65));
		sprintf(registro.ID, "%.6d ", i);
		sprintf(registro.salario, "%d ", (rand()%100000));

		write(fd_destino, &registro, sizeof(struct registro_EMPLEADO));
		write(fd_destino, "\n", 2);
	}

	close(fd_destino);
}