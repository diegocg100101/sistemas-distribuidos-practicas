#include <stdio.h>
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

    info_auto uber;
    uber.tarifa = 340.0;
    uber.tipo = UBER_PLANET;

    server = argv[1];

    if ((client = clnt_create(server, UBER, UBER_VERSION, "tcp")) == (CLIENT *)NULL)
    {
        clnt_pcreateerror(server);
        exit(2);
    }

    printf("client : Calling function.\n");
    return_value = prueba_1(&uber, client);
    if (*return_value)
        printf("\nClient : Mission accomplished.\n");
    else
        printf("\nClient : Unable to display message.\n");
    return 0;
}
