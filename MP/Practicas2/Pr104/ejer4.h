#ifndef __ejer4__
#define __ejer4__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** reservaMemoria(int nfil, int ncol);
void rellenar(int** matriz, int nfil, int ncol);
void imprimir(int** matriz, int nfil, int ncol);
int* minCol(int** matriz, int nfil, int ncol);
void liberar(int** matriz, int nfil, int ncol);
#endif