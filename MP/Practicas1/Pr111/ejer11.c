#include "ejer11.h"

int es_prefijo(char cadena[], char prefijo[]){
    int ncad=strlen(cadena);
    int npref=strlen(prefijo);
    if(strstr(cadena, prefijo)==NULL){
        return 0;
    }
    else{
        for(int i=0; i<npref; i++){
            if(cadena[i]!=prefijo[i]){
                return 0;
            }
        }
    }
    return 1;
}

int es_sufijo(char cadena[], char sufijo[]){
    int ncad=strlen(cadena);
    int nsuf=strlen(sufijo);
    if(strstr(cadena, sufijo)==NULL){
        return 0;
    }
    else{
        for(int i=ncad-1; i>=0; i--){
            for(int j=nsuf-1; j>=0; j--){
                if(cadena[i]!=sufijo[j]){
                    return 0;
                }
            }
        }
    }
    return 1;
}