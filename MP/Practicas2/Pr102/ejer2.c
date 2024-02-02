#include "ejer2.h"

void rellenaAleatorio(int vector[], int longitud){
    srand(time(NULL));
    for(int i=0; i<longitud; i++){
        vector[i]=(rand()%MAX);
    }
}

void contarmayoresmenores(int vector[], int longitud, int num, int* nmay, int* nmen){
    for(int i=0; i<longitud; i++){
        if(vector[i]>=num){
            *nmay+=1;
        }
        else{
            *nmen+=1;
        }
    }
}

void vectores(int vector[], int vectormay[], int vectormen[], int longitud, int num, int nmay, int nmen){
    int j=0, k=0;
    for(int i=0; i<longitud; i++){
        if(vector[i]>=num){
            if(j<nmay){
                vectormay[j]=vector[i];
                j++;
            }
        }
        else{
            if(k<nmen){
                vectormen[k]=vector[i];
                k++;
            }
        }
    }
}

void imprimir(int vector[], int n){
    for(int i=0; i<n; i++){
        printf("v[%d]=%d\n", i, vector[i]);
    }
}