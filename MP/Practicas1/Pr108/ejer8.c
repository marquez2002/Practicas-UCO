#include "ejer8.h"
#include <ctype.h>
#include <stdio.h>

void estadisticasCadena(char cadena[], int* nDig, int* nMay, int* nmin, int* nEsp){
    for(int i=0; i<30; i++){
        if(isdigit(cadena[i])!=0){
            *nDig=*nDig+1;
        }
        if(isupper(cadena[i])!=0){
            *nMay=*nMay+1;
        }
        if(islower(cadena[i])!=0){
            *nmin=*nmin+1;
        }        
        if(isspace(cadena[i])!=0){
            *nEsp=*nEsp+1;
        }
    }
}