#include "ejer9.h"


void leerMonomio(int n, monomio polinomio[]){
    for(int i=0; i<n; i++){
        printf("Introduzca el coeficiente: ");
        scanf("%d", &polinomio[i].coeficiente);
        printf("Introduzca el grado: ");
        scanf("%d", &polinomio[i].grado);
    }
}

void imprimirMonomio(int n, monomio polinomio[]){
    int i=0;
    for(int i; i<(n-1); i++){
        printf("%d·x^%d+", polinomio[i].coeficiente, polinomio[i].grado);
    }
    i=n-1;
    printf("%d·x^%d\n\n", polinomio[i].coeficiente, polinomio[i].grado);
}

void mayormenor(int n, monomio polinomio[], monomio mayor[], monomio menor[]){
    mayor->coeficiente=polinomio[0].coeficiente;
    mayor->grado=polinomio[0].grado;
    menor->coeficiente=polinomio[0].coeficiente;
    menor->grado=polinomio[0].grado;

    for(int i=1; i<n; i++){
        if(mayor->grado<polinomio[i].grado){
            mayor->coeficiente=polinomio[i].coeficiente;
            mayor->grado=polinomio[i].grado;
        }
        if(menor->grado>polinomio[i].grado){
            menor->coeficiente=polinomio[i].coeficiente;
            menor->grado=polinomio[i].grado;
        }
    }
}

void resultadox(int n, monomio polinomio[], int x){
    int resultado=0;
    for(int i=0; i<n; i++){
        resultado=resultado+polinomio[i].coeficiente*pow(x, (polinomio[i].grado));
    }
    printf("%d\n", resultado);
}
