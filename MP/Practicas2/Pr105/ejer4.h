/**
 * @file ejer3.h
 * @author Gonzalo Márquez (i02matog@uco.es)
 * @brief Crear una matriz con reserva de memoria, rellenar, imprimir y obtener minimo de cada columna
 * @version 0.1
 * @date 2022-03-30
 * 
 * @fn reservarMemoria
 * @param nFil
 * @param nCol
 * @return vector
 * 
 * Otras funciones que aparecen serán:
 * @li rellenaMatriz
 * @li imprimeMatriz
 * @li minCol
 * 
 */
#ifndef __ejer4__
#define __ejer4__
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int** reservarMemoria(int nFil, int nCol);
void rellenaMatriz (int **matriz, int nFil, int nCol);
void imprimeMatriz (int **matriz, int nFil, int nCol);
int* minCol(int **matriz, int nFil, int nCol);
#endif