#include "pr302.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    char c, *nombre=NULL;
    int longitud=0;
    printf("Nombre del archivo a generar: ");
    while((c=getchar())!='\n'){
        if((nombre=(char*)realloc(nombre, (longitud+1)*sizeof(char)))==NULL){
            printf("ERROR al introducir el nombre");
            return -1;
        }
        nombre[longitud]=c;
        longitud++;
    }

    int num;
    printf("Introduce la cantidad de numeros a introducir: ");
    scanf("%d", &num);

    int min, max;
    printf("Introduce el valor maximo: ");
    scanf("%d", &max);
    printf("Introduce el valor minimo: ");
    scanf("%d", &min);

    fichero(nombre, num, min, max);


}