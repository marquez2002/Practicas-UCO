#include "pr306.h"
#include <stdio.h>
#include <stdlib.h>

float mediaFichero(char const *nombre){
    int* vector, nNumeros;
    FILE* f;
    if((f=fopen(nombre, "rb"))==NULL){
        printf("ERROR al abrir el archivo\n");
        exit(0);
    }
    fseek(f, 0, SEEK_END);
    nNumeros=(ftell(f)/sizeof(int));
    fclose(f);
    float media=0;
    f=fopen(nombre, "rb");
    vector=(int*)calloc(nNumeros, sizeof(int));
    fread(vector, sizeof(int), nNumeros, f);
    fclose(f);
    int n=0;
    for(int i=0; i<nNumeros; i++){
        if(vector[i]%2==0){
            media=media+vector[i];
            n++;
        }
    }
    return (media/n);
}