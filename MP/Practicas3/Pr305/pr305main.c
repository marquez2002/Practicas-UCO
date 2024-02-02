#include "pr305.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[]){
    if(argc<5){
        printf("ERROR, al ejecutar se deben introducir 4 elementos\n");
        return -1;
    }

    if((atoi(argv[2]))<1){
        printf("ERROR introduzca numeros positivos\n");
        return -1;
    }

    if((atoi(argv[4]))<(atoi(argv[3]))){
        printf("ERROR valor maximo extremo menor que el minimo\n");
        return -1;
    }

    if(rellenarFichero(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]))==-1){
        printf("Se ha producido un error al crear el fichero\n");
        return -1;
    }
    return 0;

}