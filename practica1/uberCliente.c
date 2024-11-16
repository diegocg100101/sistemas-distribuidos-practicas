#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_SIZE 400

/*
 *  sintaxis: cliente <direccion IP> <# puerto>
 */

int conectar_servidor(char *ip, char *puerto, struct sockaddr_in *serv)
{
   int fd = socket(AF_INET, SOCK_STREAM, 0);
   if (fd == -1)
   {
      perror("\nError, no se pudo abrir el socket.\n\n");
      return -1;
   }

   // Configuración del servidor
   serv->sin_family = AF_INET;
   serv->sin_addr.s_addr = inet_addr(ip);
   serv->sin_port = htons(atoi(puerto));

   if (connect(fd, (struct sockaddr *)serv, sizeof(*serv)) < 0)
   {
      printf("\nNo se pudo realizar la conexión remota.\n");
      close(fd);
      return -1;
   }
   return fd;
}

int main(int argc, char *argv[])
{
   char request[20];
   long int placas;
   long int costo;

   printf("Escribe la petición: \n");
   scanf("%s", request);

   char buffer[BUF_SIZE];

   if (argc != 3)
   {
      puts("\nModo de uso: ./clienteClima <direccion IP> <# puerto>");
      exit(-1);
   }

   printf("\nAbriendo el socket...\n");
   int fd = socket(AF_INET, SOCK_STREAM, 0);
   if (fd == -1)
      perror("\nError, no se pudo abrir el socket.\n\n");
   else
      perror("\nSocket abierto.\n");

   printf("\nAsignando atributos al socket...\n");
   struct sockaddr_in serv;
   memset(&serv, sizeof serv, 0);
   serv.sin_family = AF_INET;
   /* inet_addr convierte de cadena de caracteres (formato puntado
    * "128.112.123.1") a
    * octetos.
    */
   serv.sin_addr.s_addr = inet_addr(argv[1]);

   /* htons convierte un entero largo en octetos cuyo orden entienden
    * las funciones de los sockets
    */
   serv.sin_port = htons(atoi(argv[2]));

   if (connect(fd, (struct sockaddr *)&serv, sizeof serv) < 0)
   {
      printf("\nNo se pudo realizar la conexión remota.\n");
      exit(-1);
   }

   /*
    * Para enviar datos usar send()
    */
   if (strcmp(request, "viaje") == 0)
   {
      send(fd, request, strlen(request) + 1, 0);
      read(fd, buffer, BUF_SIZE);
      if (strcmp(buffer, "No hay conductores") == 0)
      {
         printf("No hay conductores\n");
         exit(-1);
      }
      else
      {
         sscanf(buffer, "%ld;%ld", &placas, &costo);
         printf("Viaje en curso...\nPlacas: %ld Costo: %ld\n", placas, costo);

         close(fd);

         sleep(5);

         fd = conectar_servidor(argv[1], argv[2], &serv);
         if (fd == -1)
            exit(-1);

         memset(request, 0, sizeof(request));
         sprintf(request, "terminado;%ld", placas);
         send(fd, request, strlen(request) + 1, 0);
         memset(buffer, 0, BUF_SIZE);
         read(fd, buffer, BUF_SIZE);
         printf("\n%s", buffer);

         close(fd);
      }
   }
   else if (strcmp(request, "estado") == 0)
   {
      send(fd, request, strlen(request) + 1, 0);
      read(fd, buffer, BUF_SIZE);
      printf("\n%s", buffer);
   } else {
      printf("Petición inválida\n");
      exit(-1);
   }

   printf("\nLa petición fue enviada al servidor.\n\n");

   return 0;
}
