#include "micro1.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
    if(argc<4){
        printf("ERROR faltan archivos\n");
        return -1;
    }

    nuevoFichero(argv[1], argv[2], argv[3]);
}