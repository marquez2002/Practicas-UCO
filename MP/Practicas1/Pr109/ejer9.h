#ifndef __ejer9__
#define __ejer9__
#include <stdio.h>
#include <math.h>

typedef struct{
    int coeficiente;
    int grado;
}monomio;

void leerMonomio(int n, monomio polinomio[]);
void imprimirMonomio(int n, monomio polinomio[]);
void mayormenor(int n, monomio polinomio[], monomio mayor[], monomio menor[]);
void resultadox(int n, monomio polinomio[], int x);
#endif