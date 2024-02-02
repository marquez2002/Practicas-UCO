#include <stdio.h>
#include "minimo.c"

int main(){
    int num1, num2, resultado;
    printf("Introduce el valor 1: ");
    scanf("%d", &num1);
    printf("Introduce el valor 2: ");
    scanf("%d", &num2);

    printf("\n\nEl valor minimo por medio de referencia sera: %d\n", minimo(num1, num2));
    minimoReferencia(num1, num2, &resultado);
    printf("El valor minimo mediante referencia sera: %d\n", resultado);
}