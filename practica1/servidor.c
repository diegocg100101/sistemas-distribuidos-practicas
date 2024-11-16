#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ETHSIZE 400
#define PORT 8000
#define BUF_SIZE 5
#define NUM_INSCRIPCIONES 500

int main()
{
    int posicion = 0;
    char inscripciones[NUM_INSCRIPCIONES][100];   
    char mensaje[ETHSIZE];
    char datos_para_el_cliente[100];

    memset(inscripciones, 0, sizeof(inscripciones));

    // Datos a recibir
    char nombre[50];
    long int clave;
    char grupo[20];

    // Se crea el socket con protocolo TCP
    printf("\nSe creará el socket...\n");
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0); // Protocolo TCP
    if (socket_fd == -1)
    {
        perror("\nerror, no se pudo crear el socket.\n");
        exit(-1);
    }
    else
        perror("\nSocket creado.\n");

    printf("\nSe asignarán los atributos al socket...\n");

    // Estructura con la información para recibir peticiones con cualquier
    // dirección IP en el puerto 8000
    struct sockaddr_in addr_serv;
    memset(&addr_serv, sizeof addr_serv, 0);
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY cualquier dirección IP
    addr_serv.sin_port = htons(PORT);

    // Asocia el socket creado con las direcciones IP y el puerto
    int idb = bind(socket_fd, (struct sockaddr *)&addr_serv, sizeof addr_serv);
    if (idb < 0)
        perror("\nNo se asignaron los atributos.\n");
    else
        perror("\nSi se asignaron los atributos.\n");

    if (listen(socket_fd, BUF_SIZE) < 0)
    {
        perror("\nError al tratar de escuchar.\n");
        exit(-1);
    }

    printf("\nEsperando una conexión de un cliente en el puerto %d...\n", PORT);
    socklen_t addrLen; // Define tamaño del socket

    int cupo = 50;
    int final = 0;
    while (final > -1)
    {
        // Acepta la conexión y almacena el identificador del socket de la petición
        int newSocket_fd = accept(socket_fd, (struct sockaddr *)&addr_serv, &addrLen);
        if (newSocket_fd < 0)
        {
            perror("\nError al aceptar la conexión del cliente.\n");
            exit(-1);
        }

        // Se lee la cadena de texto  obtenida en la petición
        int size_recv = read(newSocket_fd, mensaje, ETHSIZE);

        sscanf(mensaje, "%[^;];%ld;%[^;]", nombre, &clave, grupo);

        printf("\nLa petición recibida fue: %s.\n", mensaje);

        // Almacena en el arreglo
        strcpy(inscripciones[posicion], mensaje);

        // Depura para mostrar las inscripciones hechas
        printf("Inscripciones realizadas:\n");
        for(int i = 0; i < NUM_INSCRIPCIONES; i++) {
            if(inscripciones[i][0] != '\0'){
                printf("%s\n", inscripciones[i]);
            }
        }

        cupo --;
        sprintf(datos_para_el_cliente, "\nEl número de inscripción es: %d\nEl cupo del grupo es: %d", posicion + 1, cupo);

        /* Aqui enviamos los datos al cliente */
        // Se especifica el socket, los datos a enviar y el tamaño de bytes
        send(newSocket_fd, datos_para_el_cliente, strlen(datos_para_el_cliente) + 1, 0);

        printf("\nYa envié el mensaje al cliente.\n\n");

        printf("\nEsperando una conexión de un cliente en el puerto %d...\n", PORT);

        posicion ++;
    }

    return 0;
}
