#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "uber.h"

int main(int argc, char *argv[])
{
    CLIENT *client;
    int *return_value, filler;
    char *server;

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

    int final = 0;

    while (final > -1)
    {
        printf("\nEstado:\n");

        info_servicio *informacion = estado_servicio_1(client);

        printf("Autos libres: %i\nGanancias: %f\nViajes realizados: %i\n", informacion->autos_libres, informacion->ganancia, informacion->viajes);

        sleep(2);
    }

    return 0;
}
