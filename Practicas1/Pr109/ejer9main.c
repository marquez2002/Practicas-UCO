#include "ejer9.h"
#include <stdio.h>


int main(){
    int n;
    printf("¿Cuantos monomios habra en el polinomio?:");
    scanf("%d", &n);
    monomio polinomio[n];
    leerMonomio(n, polinomio);
    imprimirMonomio(n, polinomio);
    monomio mayor[1];
    monomio menor[1];
    mayormenor(n, polinomio, mayor, menor);
    printf("El mayor monomio es %d·x^%d y el menor monomo %d·x^%d\n", mayor->coeficiente, mayor->grado, menor->coeficiente, menor->grado);
    int x;
    printf("Introduce un valor para la funcion -> x=");
    scanf("%d", &x);
    resultadox(n, polinomio, x);
    

}