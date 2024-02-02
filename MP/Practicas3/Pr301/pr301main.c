#include "pr301.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    int longitud=0;
    char aux, *nombre1=NULL, *nombre2;
    printf("Introduzca el nombre del archivo que desea poner en mayuscula\n");
    while((aux=getchar())!='\n'){
        if((nombre1=(char*)realloc(nombre1, (longitud+1)*sizeof(char)))==NULL){
            printf("Error al guardar el nombre\n");
            return(-1);
        }
        nombre1[longitud]=aux;
        longitud++;
    }
    nombre2=reservaMemoriaNombre(longitud);
    creaNombre(nombre1, nombre2);
    int n=copiaArchivo(nombre1, nombre2);
    switch(n){
        case 0: 
            printf("Todo correcto\n");
        break;

        case 1: 
            printf("ERROR al abrir el archivo %s\n", nombre1);
        break;

        case 2: 
            printf("ERROR al abrir el archivo %s\n", nombre2);
        break;
    }
    return 0;
}