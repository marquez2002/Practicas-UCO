/**
 * @file ejer3.h
 * @author Gonzalo 
 * @brief describe the funtions of ejer3.h
 * @version 0.1
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ejer3__
#define __ejer3__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief struct
 * @param nombre
 * @param dorsal
 * @param peso
 * @param estatura
 */

typedef struct{
    char nombre[50];
    int dorsal;
    float peso;
    float estatura;
}jugador;

jugador* reservarMemoria(int n);
jugador listar();

/**
 * @fn crearEquipo(jugador equipo[], int n);
 * @brief Crear una estructura dinamica para el equipo
 * @param jugador equipo
 * @param n
 * @return void
 */

void crearEquipo(jugador equipo[], int n);
void imprimir(jugador equipo[], int n);
int borrarJugadores(jugador equipo[], int* n, char letra);

#endif