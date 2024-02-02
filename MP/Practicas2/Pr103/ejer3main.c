#include "ejer3.h"

int main(){
    
    int n;
    printf("Cuantos jugadores hay en el equipo: ");
    scanf("%d", &n);
    printf("\n");

    jugador* equipo;
    equipo=reservarMemoria(n);

    crearEquipo(equipo, n);
    imprimir(equipo, n);

    char letra;
    printf("Que letra desea introducir para eliminar nombres: ");
    scanf(" %c", &letra);

    n=borrarJugadores(equipo, &n, letra);
    imprimir(equipo, n);


}