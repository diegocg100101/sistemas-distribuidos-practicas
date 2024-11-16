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

int main(int argc, char *argv[])
{
    // Datos para mandar al servidor
    char nombre[50];
    long int clave;
    char grupo[20];

    // Variable que almacena el mensaje codificado
    char mensaje[200];

    printf("Escribe el nombre: \n");
    scanf("%[^\n]", nombre);

    printf("Escribe la clave de UEA: \n");
    scanf("%ld", &clave);

    printf("Escribe el grupo: \n");
    scanf("%s", grupo);


    // Se codifica el mensaje
    sprintf(mensaje, "%s;%ld;%s", nombre, clave, grupo);

    char buffer[BUF_SIZE];

    if (argc != 3)
    {
        puts("\nModo de uso: ./cliente <direccion IP> <# puerto>");
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
    serv.sin_addr.s_addr = inet_addr(argv[1]);
    serv.sin_port = htons(atoi(argv[2]));

    if (connect(fd, (struct sockaddr *)&serv, sizeof serv) < 0)
    {
        printf("\nNo se pudo realizar la conexión remota.\n");
        exit(-1);
    }

    // Se mandan el mensaje codificado
    send(fd, mensaje, strlen(mensaje), 0);

    printf("\nLa petición fue enviada al servidor.\n\n");

    // Se recibe el mensaje del servidor
    read(fd, buffer, BUF_SIZE);

    printf("\nEstos son los datos enviados por el servidor:\n");
    printf("%s.\n\n", buffer);

    return 0;
}
