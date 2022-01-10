/* 
Proyecto 2
Nombre: Hernández Trejo Enrique Alberto
Grupo: Sistemas Operativos 2CM16
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int revisa_carpetas(char dir_name[], char name[])
{
   struct stat st_buf;
   struct dirent *dit;
   DIR *dip;
   char direc[255], buffer[255], compara[255];
   int status, j = ' ';

   if ((dip = opendir(dir_name)) == NULL)
   {
      perror("opendir");
      return 0;
   }

   while((dit = readdir(dip)) != NULL)
   {
      strcat(strcat(strcpy(buffer, dir_name), "/"), dit->d_name);
      strcpy(compara, dit->d_name);

      status = stat(buffer, &st_buf);
      if(status != 0){
         printf("Error, errno = %d\n", errno);
      }

      if (S_ISREG(st_buf.st_mode))
      {
         if(strcmp(compara, name) == 0)
         printf("Archivo: %s\n", buffer);
      }

      if (S_ISDIR(st_buf.st_mode))
      {
         if(compara[0] == '.')
            continue;
         else
         {
            if(strcmp(compara, name) == 0)
            printf("Directorio: %s\n", buffer);
            revisa_carpetas(buffer, name);
         }
      }
   }

   if (closedir(dip) == -1)
   {
      perror("closedir");
      return 0;
   }
}

int main(int argc, char *argv[])
{
   if (argc == 1 || argc == 2)
   {
      printf("La entrada debe de ser tipo:\n./nombre_del_programa ruta_absoluta nombre_de_archivo_o_carpeta \n");
      return 0;
   }

   return revisa_carpetas(argv[1], argv[2]);

}