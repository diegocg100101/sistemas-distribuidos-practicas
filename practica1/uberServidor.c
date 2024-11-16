#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define ETHSIZE 400
#define PORT 8000
#define BUF_SIZE 5
#define NUM_AUTOS 1

int main()
{
    char request[ETHSIZE];
    char datos_para_el_cliente[ETHSIZE];
    bool autos[NUM_AUTOS];
    long int placas;
    char mensaje[100];

    memset(autos, true, sizeof(autos));

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

    // Se la estructura con la información para recibir peticiones con cualquier
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

    int ganancia = 0;
    int viajes = 0;
    int costo = 0;

    int final = 0;
    while (final > -1)
    {
        struct sockaddr_in clienteIP;
        char *IPcliente = inet_ntoa(clienteIP.sin_addr);

        // Acepta la conexión y almacena el identificador del socket de la petición
        int newSocket_fd = accept(socket_fd, (struct sockaddr *)&clienteIP, &addrLen);
        if (newSocket_fd < 0)
        {
            perror("\nError al aceptar la conexión del cliente.\n");
            exit(-1);
        }

        // Se lee la cadena de texto  obtenida en la petición
        int size_recv = read(newSocket_fd, request, ETHSIZE);

        sscanf(request, "%[^;];%ld", mensaje, &placas);
        if (strcmp(mensaje, "estado") == 0)
        {
            sprintf(datos_para_el_cliente, "Ganancia: %d, Viajes: %d", ganancia, viajes);
            send(newSocket_fd, datos_para_el_cliente, strlen(datos_para_el_cliente) + 1, 0);
        }
        else if (strcmp(mensaje, "viaje") == 0)
        {
            for (int i = 0; i < NUM_AUTOS; i++)
            {
                if (autos[i])
                {   
                    costo = rand() % 1000;
                    sprintf(datos_para_el_cliente, "%d;%d", i, costo);
                    send(newSocket_fd, datos_para_el_cliente, strlen(datos_para_el_cliente) + 1, 0);
                    autos[i] = false;
                    ganancia += costo; 
                    viajes ++;
                    break;
                }
                else if (i == NUM_AUTOS - 1)
                {
                    sprintf(datos_para_el_cliente, "No hay conductores");
                    send(newSocket_fd, datos_para_el_cliente, strlen(datos_para_el_cliente) + 1, 0);
                }
            }
        }
        else if (strcmp(mensaje, "terminado") == 0)
        {
            autos[placas] = true;
            printf("\n%ld\n", placas);
            printf("\nViaje terminado\n");
            sprintf(datos_para_el_cliente, "Viaje terminado");
            send(newSocket_fd, datos_para_el_cliente, strlen(datos_para_el_cliente) + 1, 0);

        }
        else
        {
            printf("Petición inválida\n");
            strcpy(datos_para_el_cliente, "Petición inválida");
            send(newSocket_fd, datos_para_el_cliente, strlen(datos_para_el_cliente) + 1, 0);
        }

        printf("\n\nLa petición recibida fue: %s.\n", mensaje);

        printf("\nYa envié el mensaje al cliente: %s.\n\n", IPcliente);

        printf("\nEsperando una conexión de un cliente en el puerto %d...\n", PORT);

        memset(request, 0, sizeof(request));
    }

    return 0;
}