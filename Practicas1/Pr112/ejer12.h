/**
 * @file ejer12.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ejer12__
#define __ejer12__
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void rellenaVectorAleatorio(int vector[], int n, int max);
void imprimirVector(int vector[], int n);
void contarparimpar(int vector[], int n, int* impar, int* divisibles);
void formadivisibles(int vector[], int impares[], int divisible[], int n);
#endif