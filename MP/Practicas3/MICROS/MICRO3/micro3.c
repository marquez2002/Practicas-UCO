#include "micro3.h"
#include <stdio.h>
#include <stdlib.h>

void rellenaDocs(char const *archivo1, char const *archivo2, char const *archivo3){
    FILE *f1;
    FILE *f2;
    FILE *f3;
    if((f1=fopen(archivo1, "r"))==NULL){
        printf("ERROR al abrir %s", archivo1);
        exit(0);
    }
    if((f2=fopen(archivo2, "w"))==NULL){
        printf("ERROR al abrir %s", archivo2);
        exit(0);
    }
    if((f3=fopen(archivo3, "w"))==NULL){
        printf("ERROR al abrir %s", archivo3);
        exit(0);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    int n=contarN(archivo1);
    f1=fopen(archivo1, "r");
    f2=fopen(archivo2, "w");
    f3=fopen(archivo3, "w");
    char nombre[256], apellido1[256], apellido2[256];
    int edad, bilingue;
    for(int i=0; i<(n+1); i++){
        fscanf(f1, "%s %s %s %d %d\n", nombre, apellido1, apellido2, &edad, &bilingue);
        if(bilingue==1){
            fprintf(f2, "%s %s %s %d %d\n", nombre, apellido1, apellido2, edad, bilingue);
        }
        if(bilingue==0){
            fprintf(f3, "%s %s %s %d %d\n", nombre, apellido1, apellido2, edad, bilingue);
        }
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
}

int contarN(char const *nombre){
    FILE *f;
    f=fopen(nombre, "r");
    char aux[256];
    int contador=0;
    if((fgets(aux, 256, f))!=NULL || feof(f)){
        while((fgets(aux, 256, f))!=NULL){
            contador++;
        }
    }
    fclose(f);
    return contador;
}
