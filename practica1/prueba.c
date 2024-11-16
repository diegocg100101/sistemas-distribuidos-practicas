#include <stdio.h>

int main()
{
    char nombre[50] = "Diego Cantoral";
    long int clave = 4604047;
    char grupo[20] = "CG02C";
    
    // Esto será el buffer para enviar/recibir
    char mensaje[200];
    
    // CODIFICACIÓN
    // El punto y coma ';' nos servirá como separador.
    sprintf(mensaje, "%s;%ld;%s", nombre, clave, grupo);
    printf("%s\n", mensaje);

    char name[50];
    long int clv;
    char gpo[20];

    sscanf(mensaje, "%[^;];%ld;%[^;]", name, &clv, gpo);

    printf("%s, %ld, %s\n", name, clv, gpo);

    return 0;
}
