#include "pr306.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    int longitud=0;
    char aux, *nombre=NULL;
    printf("Introduzca el nombre del archivo:\n");
    while((aux=getchar())!='\n'){
        if((nombre=(char*)realloc(nombre, (longitud+1)*sizeof(char)))==NULL){
            printf("ERROR al introducir el nombre\n");
            return -1;
        }
        nombre[longitud]=aux;
        longitud++;
    }
    printf("La media de los valores pares del fichero %s es: %f\n", nombre, mediaFichero(nombre));
    return 0;
}