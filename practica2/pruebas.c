#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generar_placa(char *cadena){
	for(int i = 0; i < 3; i++) {
		cadena[i] = '0' + rand() % 10;
	}

    for (int i = 3; i < 6; i++) {
        cadena[i] = 'A' + rand() % 26;  // Genera una letra aleatoria
    }

    cadena[6] = '\0'; 
}

int main(int argc, char *argv[]) {

    char cadena[7];
    char cadena2[7];
    srand(time(NULL)); 

    generar_placa(cadena);

    generar_placa(cadena2);

    printf("%s\n%s\n", cadena, cadena2);
    return 0;
}