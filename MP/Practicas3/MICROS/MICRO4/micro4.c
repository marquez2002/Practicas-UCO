#include "micro4.h"
#include <stdio.h>
#include <stdlib.h>

void rellenar(char const *archivo1, char const *archivo2, char const *archivo3, int prioridad){
    FILE *f1;
    FILE *f2;
    FILE *f3;
    if((f1=fopen(archivo1, "rb"))==NULL){
        printf("ERROR al abrir el archivo\n");
        exit(0);
    }

    if((f2=fopen(archivo2, "wb"))==NULL){
        printf("ERROR al abrir el archivo\n");
        exit(0);
    }

    if((f3=fopen(archivo3, "wb"))==NULL){
        printf("ERROR al abrir el archivo\n");
        exit(0);
    }

    fseek(f1, 0, SEEK_END);
    int nNumeros=(ftell(f1));
    fclose(f1);
    f1=fopen(archivo1, "rb");
    

}