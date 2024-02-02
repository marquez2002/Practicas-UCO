#include "ejer8.h"
#include <stdio.h>

int main(){
    char cadena[30];
    printf("Introduzca la cadena\n");
    fgets(cadena, 30, stdin);


    int nDig=0, nMay=0, nmin=0, nEsp=0; 
    estadisticasCadena(cadena, &nDig, &nMay, &nmin, &nEsp);
    printf("La cadena %s, tiene %d digitos, %d mayusculas, %d minusculas y %d espacios\n", cadena, nDig, nMay, nmin, nDig);
    
}