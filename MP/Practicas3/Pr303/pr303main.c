#include <stdio.h>
#include <stdlib.h>
#include "pr303.h"

int main(int argc, char const *argv[]){
    if(argc<2){
        printf("Error, introduzca el nombre del fichero que desea leer.\n");
        return -1;
    }
    printf("La media de los valores del archivo %s es: %f\n", argv[1], medianum(argv[1]));
    return 0;
}