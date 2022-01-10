#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>


int main()
{
	pid_t id_proceso;
	pid_t id_padre;

	id_proceso = getpid();
	id_padre = getppid();

	printf("Identificador de proceso: %d\n", id_proceso);
	printf("Identificador de proceso padre: %d\n", id_padre);

	sleep(20);
	return 0;
}
