#include "ejer11.h"
#include <stdio.h>
#include <string.h>

int main(){
    char cadena[20];
    printf("Introduce la cadena: ");
    scanf("%s", &cadena[20]);
    char sufpre[20];
    printf("Introduce el posible sufijo o prefijo: ");
    scanf("%s", &sufpre[20]);
    printf("%s y %s", cadena, sufpre);
    if(es_prefijo(cadena, sufpre)==0){
        printf("%s no es prefijo de %s", cadena, sufpre);
    }
    else{
        printf("%s es prefijo de %s", cadena, sufpre);
    }

    if(es_sufijo(cadena, sufpre)==0){
        printf("%s no es sufijo de %s", cadena, sufpre);
    }
    else{
        printf("%s es sufijo de %s", cadena, sufpre);
    }    
}