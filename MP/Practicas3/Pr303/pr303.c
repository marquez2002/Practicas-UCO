#include <stdio.h>
#include <stdlib.h>
#include "pr303.h"

int cuentaNum(char const *nombre){
    FILE* f;
    int contador=0;
    f=fopen(nombre, "r");
    char aux[256];

    if(fgets(aux, 256, f)!=NULL || !feof(f)){
        while(fgets(aux, 256, f)!=NULL){
            contador++;
        }
    }
    return contador;
}


float medianum(char const *nombre){
    FILE* f;
    if((f=fopen(nombre, "r"))==NULL){
        printf("ERROR al abrir el archivo\n");
        exit(0);
    }
    fclose(f);
    int aux, naux=0;
    float media=0, n=cuentaNum(nombre);
    f=fopen(nombre, "r");
    char c;
    for(int i=0; i<n; i++){
        fscanf(f, "%d%c", &aux, &c);
        if(aux%2==0){
            media=media+aux;
            naux++;
        }
    }
    fclose(f);
    return(media/naux);
}