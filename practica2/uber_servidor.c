#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "uber.h"

#define NUM_AUTOS 1

static double viajes = 0;
static double ganancia = 0;

static info_auto vehiculos[NUM_AUTOS];

void *init_0_svc(void *filler, struct svc_req *req)
{

}

info_auto *solicitar_viaje_1_svc(info_auto *vehiculo, struct svc_req *req)
{
    static int ok;
    printf("Funciona??? %f %d\n", vehiculo->tarifa, vehiculo->tipo);
    ok = printf("\nEsto es una prueba\n");
    return (&ok);
}

void *terminar_viaje_2_svc(solicitud *solicitud_cliente, struct svc_req *req)
{
    // Busca el auto en el arreglo con la placa
    for (int i = 0; i < NUM_AUTOS; i++)
    {
        if (strcmp(solicitud_cliente->placas, vehiculos[i].placa) == 0)
        {
            // Cambia a disponible
            vehiculos[i].disponibilidad = false;

            // Cambia la posición del auto a la del cliente
            vehiculos[i].posXY = solicitud_cliente->posicion_final;

            // Suma el costo a la ganancia
            ganancia += solicitud_cliente->costo;

            // Aumenta el número de viajes
            viajes++;

            printf("Auto con placas: %s está disponible\n", solicitud_cliente->placas);
        }
        return NULL;
    }
}

info_servicio *estado_servicio(void *filler, struct svc_req *req)
{
    // Inicializa estructura
    static info_servicio estado;

    // Almacena el número de viajes realizados al momento
    estado.viajes = viajes;

    // Almacena la ganancia total al momento
    estado.ganancia = ganancia;

    // Cuenta los autos disponibles y los almacena

    /*
    for (int i = 0; i < NUM_AUTOS; i++){
        if(vehiculos[NUM_AUTOS].disponibilidad == true) {
            estado.autos_libres ++;
        }
    }*/

    estado.autos_libres = 1;

    return &estado;
}
