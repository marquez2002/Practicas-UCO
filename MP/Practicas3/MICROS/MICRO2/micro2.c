#include "micro2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rellenarFichero(char const *archivo1, char const *archivo2, char const *archivo3){
    FILE *f1;
    FILE *f2;
    FILE *f3;

    if((f1=fopen(archivo1, "r"))==NULL){
        printf("ERROR al abrir el archivo %s", archivo1);
        exit(0);
    }
    fclose(f1);
    if((f2=fopen(archivo2, "r"))==NULL){
        printf("ERROR al abrir el archivo %s", archivo2);
        exit(0);
    }
    fclose(f2);
    if((f3=fopen(archivo3, "a"))==NULL){
        printf("ERROR al abrir el archivo %s", archivo3);
        exit(0);
    }
    fclose(f3);  

    int n=cuentaElementos(archivo1);
    f1=fopen(archivo1, "r");
    f2=fopen(archivo2, "r");
    f3=fopen(archivo3, "w");
    printf("%d\n", n);
    char autor[256], titulo[256];
    int i=0, j=0;
    for(int i=0; i<(n+1); i++){
        fgets(titulo, 256, f1);
        if(titulo[strlen(titulo)-1]=='\n'){
            titulo[strlen(titulo)-1]=0;
        }
        fgets(autor, 256, f2);
        if(autor[strlen(autor)-1]=='\n'){
            autor[strlen(autor)-1]=0;
        }
        fprintf(f3, "%s -> %s\n", titulo, autor);
    }
    printf("TODO CORRECTO\n");
    fclose(f1);
    fclose(f2);
    fclose(f3);
}

int cuentaElementos(char const *nombre){
    FILE *f;
    int contador;
    f=fopen(nombre, "r");
    char aux[256];
    if((fgets(aux, 256, f))!=NULL || feof(f)){
        while(fgets(aux, 256, f)!=NULL){
            contador++;
        }
    }
    fclose(f);
    return contador;
}