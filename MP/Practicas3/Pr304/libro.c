#include "libro.h"
#include "pr304.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int existeLibro(char const *nombre, char* titulo){
    FILE* f;
    f=abreLectura(nombre);
    if(f==NULL){
        return 0;
    }
    char aux[256];
    if(fgets(aux, 256,f)!=NULL || feof(f)){
        while(fgets(aux, 256, f)!=NULL){
            if(strcmp(aux, titulo)==0){
                fclose(f);
                return 2;
            }
            int i=0; 
            while(fgets(aux, 256, f)!=NULL && i<2){
                i++;
            }
        }
        fclose(f);
        return 1;
    }
}

void introducirNuevoLibro(char const *nombre){
    FILE* f;
    f=abreAdjuntar(nombre);
    if(f==NULL){
        printf("ERROR no se puede abrir el archivo\n");
        exit(-1);
    }
    fclose(f);
    char aux[256];
    float precio;
    int unidades;
    printf("Introduzca el título\n");
    fgets(aux, 256, stdin);
    int estado=existeLibro(nombre, aux);
    switch(estado){
        case 0:
            printf("El archivo no existe\n");
        break;

        case 1:
            f=abreAdjuntar(nombre);
            fputs(aux, f);
            printf("Introduzca el nombre del autor:\n");
            fgets(aux, 256, stdin);
            fputs(aux, f);
            printf("Introduzca el precio del libro:\n");
            scanf("%f", &precio);
            fprintf(f, "%f ", precio);
            printf("Introduzca el numero de unidades del libro: \n");
            scanf("%d", &unidades);
            fprintf(f, "%d\n", unidades);
            fclose(f);
        break;

        case 2:
            printf("El libro ya existe\n");
        break;
    }
}