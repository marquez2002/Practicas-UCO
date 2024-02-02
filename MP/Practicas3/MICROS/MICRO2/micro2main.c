#include "micro2.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
    if(argc<4){
        printf("ERROR en la estructura de la ejecución\nLa estructura debe ser ./micro2 fichero1 fichero2 fichero3\n");
        return -1;
    }
    rellenarFichero(argv[1], argv[2], argv[3]);

}