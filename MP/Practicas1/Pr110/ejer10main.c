#include "ejer10.h"

int main(){
    printf("Introduce la longitud del vector:");
    int n;
    scanf("%d", &n);
    double vector[n];
    leerVector(vector, n);
    imprimirVector(vector, n);
    double suma=0;
    sumaPositivos(vector, n, &suma);
}