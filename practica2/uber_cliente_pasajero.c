#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include "uber.h"


double calcular_distancia(posicion posicion_inicial, posicion posicion_final) {
    double distancia;
    distancia = sqrt(pow(posicion_final.x - posicion_inicial.x, 2) 
        + pow(posicion_final.y - posicion_inicial.y, 2));

    return distancia;
}

int main(int argc, char *argv[])
{
    CLIENT *client;
    int *return_value, filler;
    char *server;
    char tipo[20];

	srand(time(NULL));

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s host_name\n", *argv);
        exit(1);
    }

    server = argv[1];

    if ((client = clnt_create(server, UBER, UBER_VERSION, "tcp")) == (CLIENT *)NULL)
    {
        clnt_pcreateerror(server);
        exit(2);
    }

    //printf("client : Calling function.\n");

    posicion posicion_cliente;
    posicion_cliente.x = rand() % 50;
    posicion_cliente.y = rand() % 50;

    double recorrido = 0;

    info_auto* vehiculo = solicitar_viaje_1(posicion_cliente, client);

    if(vehiculo != NULL){
        printf("\nSe encontró vehiculo\nPlacas: %s\n", vehiculo->placa);
        sleep(5);

        posicion posicion_final;
        posicion_final.x = rand() % 50;
        posicion_final.y = rand() % 50;

        recorrido = calcular_distancia(posicion_cliente, posicion_final);

        if(vehiculo->tipo == 0) {
            strcpy(tipo, "UberPlanet");
            recorrido *= 10;
        } else if (vehiculo->tipo == 1)
        {
            strcpy(tipo, "UberXL");
            recorrido *= 15;
        } else {
            strcpy(tipo, "UberBlack");
            recorrido *= 25;
        }
        

        terminar_viaje_1(posicion_final, recorrido, vehiculo->placa, client);
        printf("\n¡Viaje concluido con éxito!\nCosto: %f\nTipo: %s\n", recorrido, tipo);
    } else {
        printf("No se encontró vechiculo\n");
    }
    return 0;
}
