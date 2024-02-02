#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int** reservarMemoria(int nFil, int nCol){
    int** matriz;
    matriz=(int**)malloc(nFil*sizeof(int*));
    for(int i=0; i<nFil; i++){
            matriz[i]=(int*)malloc(nCol*sizeof(int));
        }
    return matriz;
}

void rellenaMatriz (int **matriz, int nFil, int nCol){
    srand(time(NULL));
    for(int i=0; i<nFil; i++){
        for(int j=0; j<nCol; j++){
            matriz[i][j]=((rand()%19)+1);
        }
    }
}

void imprimeMatriz (int **matriz, int nFil, int nCol){
    for(int i=0; i<nFil; i++){
        for(int j=0; j<nCol; j++){
            printf("%d  ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int* minCol(int **matriz, int nFil, int nCol){
    int* vector2;
    vector2=(int*)malloc(nCol*sizeof(int));
    
    for(int i=0; i<nFil; i++){
        vector2[i]=matriz[i][0];            
    }
    
    for(int i=0; i<nFil; i++){
        for(int j=0; j<nCol; j++){
            if(vector2[i]>matriz[j][i]){
                vector2[i]=matriz[j][i];
            }
        }
    }
    return vector2;
}

