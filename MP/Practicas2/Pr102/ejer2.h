#ifndef __ejer2__
#define __ejer2__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 30

void rellenaAleatorio(int vector[], int longitud);
void vectores(int vector[], int vectormay[], int vectormen[], int longitud, int num, int nmay, int nmen);
void imprimir(int vector[], int n);
void contarmayoresmenores(int vector[], int longitud, int num, int* nmay, int* nmen);
#endif