#include "micro4.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
    if(argc<4){
        printf("ERROR al introducir el ejecutable\n");
        return -1;
    }
    int prioridad;
    printf("x=");
    scanf("%d", &prioridad);
    rellenar(argv[1], argv[2], argv[3], prioridad);
}