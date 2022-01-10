#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
   int bytes_enviados, bytes_leidos, bytes_enviados1, bytes_leidos1, i, descriptor_archivo[2], descriptor_archivo1[2];
   char buffer[BUFSIZ + 1], buffer1[BUFSIZ + 1];
   pid_t pid;
   if(pipe(descriptor_archivo) == 0 && pipe(descriptor_archivo1) == 0){
      pid = fork();
      if (pid == -1) {
         perror("Error al ejecutar fork");
         exit(-1);
      }
      if (pid == 0) { //Proceso hijo
         for(i = 97; i < 123 ; i++){
            bytes_enviados1 = write(descriptor_archivo1[1], (char *) &(i), sizeof(char));
            printf("El proceso hijo ha enviado por la tuberia %d bytes\n", bytes_enviados1);
            memset(buffer, '\0', sizeof(buffer));
            bytes_leidos = read(descriptor_archivo[0], buffer, BUFSIZ);
            printf("El proceso hijo ha leído %d bytes y el contenido es: %s\n", bytes_leidos, buffer);
            
         }
         exit(0);
      }
      else { //Proceso padre
         for( i = 65; i < 91; i++){
            bytes_enviados = write(descriptor_archivo[1], (char *) &i, sizeof(char));
            printf("El proceso padre ha enviado por la tuberia %d bytes\n", bytes_enviados);
            memset(buffer1, '\0', sizeof(buffer1));
            bytes_leidos1 = read(descriptor_archivo1[0], buffer1, BUFSIZ);
            printf("El proceso padre ha leído %d bytes y el contenido es: %s\n", bytes_leidos1, buffer1);
         }
      }
      sleep(5);
   }
   exit(0);
}

