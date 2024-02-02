#include "ejer4.h"

int** reservaMemoria(int nfil, int ncol){
    int** matriz;
    matriz=(int**)malloc(nfil*sizeof(int*));
    for(int i=0; i<nfil; i++){
        matriz[i]=(int*)malloc(ncol*sizeof(int));
    }
    return matriz;
}

void rellenar(int** matriz, int nfil, int ncol){
    srand(time(NULL));
    for(int i=0; i<nfil; i++){
        for(int j=0; j<ncol; j++){
            matriz[i][j]=(rand()%20)+1;
        }
    }
}

void imprimir(int** matriz, int nfil, int ncol){
    for(int i=0; i<nfil; i++){
        for(int j=0; j<ncol; j++){
            printf("%d  ", matriz[i][j]);
        }
        printf("\n");
    }
}

int* minCol(int** matriz, int nfil, int ncol){
    int* vector;
    vector=(int*)malloc(ncol*sizeof(int));
    for(int i=0; i<ncol; i++){
        vector[i]=matriz[0][i];
    }
    for(int i=0; i<ncol; i++){
        for(int j=0; j<nfil; j++){
            if(vector[i]>matriz[j][i]){
                vector[i]=matriz[j][i];
            }
        }        
    }
    return vector;
}

void liberar(int** matriz, int nfil, int ncol){
    for(int i=0; i<nfil; i++){
            free(matriz[i]);
    }
    free(matriz);
}