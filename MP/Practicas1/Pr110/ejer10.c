#include "ejer10.h"

void leerVector(double vector[], int n){
    printf("Introduce el vector:\n");
    for(int i=0; i<n; i++){
        printf("v[%d]=", i);
        scanf("%lf", &vector[i]);
    }
}

void imprimirVector(double vector[], int n){
    for(int i=0; i<n; i++){
        printf("v[%d]=%lf\n", i, vector[i]);
    }
}

void sumaPositivos(double vector[], int n, double* suma){
    for(int i=0; i<n; i++){
        if(vector[i]>0){
            *suma=*suma+vector[i];
        }
    }
    printf("El resultado de la suma de positivos es: %lf\n", *suma);
}