#include "micro1.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void nuevoFichero(char const *archivo1, char const *archivo2, char const *archivo3){
    FILE* f1;
    FILE* f2;
    FILE* f3;
    if((f1=fopen(archivo1, "r"))==NULL){
        printf("ERROR al abrir el archivo %s\n", archivo1);
        exit(0);
    }
    fclose(f1);

    if((f2=fopen(archivo2, "r"))==NULL){
        printf("ERROR al abrir el archivo %s\n", archivo2);
        exit(0);
    }
    fclose(f2);

    if((f3=fopen(archivo3, "a"))==NULL){
        printf("ERROR al abrir el archivo %s\n", archivo3);
        exit(0);
    }
    fclose(f3);

    char nombre[256], apellido1[256], apellido2[256], c;
    int edad, bilingue;
    int n=cuentaAlum(archivo1), n2=cuentaAlum(archivo2);
    f1=fopen(archivo1, "r");
    f3=fopen(archivo3, "a");
    for(int i=0; i<(n+1); i++){
        fscanf(f1, "%s%c%s%c%s%c%d%c%d\n", nombre, &c, apellido1, &c, apellido2, &c, &edad, &c, &bilingue);
        if(bilingue==1){
            fprintf(f3, "%s %s %s %d %d\n", nombre, apellido1, apellido2, edad, bilingue);
        }
    }
    fclose(f1);
    fclose(f3);
    char cadena1[256], cadena2[256];
    f2=fopen(archivo2, "r");
    f3=fopen(archivo3, "a");
    for(int i=0; i<(n2+1); i++){
        int igual=0;
        fgets(cadena1, 256 ,f2);
        fscanf(f2, "%s%c%s%c%s%c%d%c%d\n", nombre, &c, apellido1, &c, apellido2, &c, &edad, &c, &bilingue);
        for(int i=0; i<(n+1);i++){
            fgets(cadena2, 256 ,f3);
            if(cadena1==cadena2){
                igual=1;
            }
        }
        if(igual==0){
            if(bilingue==1){
                fprintf(f3, "%s %s %s %d %d\n", nombre, apellido1, apellido2, edad, bilingue);
            }
        }
    }
    fclose(f2);
    fclose(f3);
}

int cuentaAlum(char const *nombre){
    FILE* f;
    int contador=0;
    f=fopen(nombre, "r");
    char aux[256];
    if(fgets(aux, 256, f)!=NULL || feof(f)){
        while(fgets(aux, 256, f)!=NULL){
            contador++;
        }
    }
    fclose(f);
    return contador;
}