#include "ejer12.h"

void rellenaVectorAleatorio(int vector[], int n, int max){
    srand(time(NULL));
    for(int i=0; i<n; i++){
            vector[i]=(rand()%(max+1));
    }
}

void imprimirVector(int vector[], int n){
    for(int i=0; i<n; i++){
        printf("v[%d]=%d\n", i, vector[i]);
    }
    printf("\n");
}

void contarparimpar(int vector[], int n, int* impar, int* divisibles){
    for(int i=0; i<n; i++){
        if(vector[i]%2!=0){
            *impar+=1;
        }
        if(vector[i]%3==0){
            *divisibles+=1;
        }
    }
}

void formadivisibles(int vector[], int impares[], int divisible[], int n){
    int j=0, k=0;
    for(int i=0; i<n; i++){
        if(vector[i]%2!=0){
            impares[j]=vector[i];
            j++;
        }
        if(vector[i]%3==0){
            divisible[k]=vector[i];
            k++;
        }
    }
}

