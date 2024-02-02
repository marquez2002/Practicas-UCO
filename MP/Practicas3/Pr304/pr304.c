#include "pr304.h"
#include <stdio.h>

FILE *abreLectura(const char* nombre){
    FILE *f;
    f=fopen(nombre, "r");
    return f;
}

FILE *abreNuevo(const char* nombre){
    FILE *f;
    f=fopen(nombre, "w");
    return f;
}

FILE *abreAdjuntar(const char* nombre){
    FILE *f;
    f=fopen(nombre, "a");
    return f;
}