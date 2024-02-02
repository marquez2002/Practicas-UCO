#include "ejer12.h"


int main(){
    int n, max;
    printf("¿Cuantos elementos tendra el vector?: ");
    scanf("%d", &n);
    printf("¿Cual sera el maximo que pueda tomar el vector?: ");
    scanf("%d", &max);
    int vector[n];

    rellenaVectorAleatorio(vector, n, max);
    imprimirVector(vector, n);
    int impar=0, divisibles=0;
    contarparimpar(vector, n, &impar, &divisibles);
    int impares[impar];
    int divisible[divisibles];
    formadivisibles(vector, impares, divisible, n);
    printf("Impresion de vector impares: \n");
    imprimirVector(impares, impar);
    printf("Impresion de vector divisibles por 3: \n");
    imprimirVector(divisible, divisibles);
}