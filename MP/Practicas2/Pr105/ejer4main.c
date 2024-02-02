#include "ejer4.h"


int main(){
    int nFil, nCol;
    printf("Introduce el numero de filas: ");
    scanf("%d", &nFil);
    printf("Introduce el numero de columnas: ");
    scanf("%d", &nCol);
    int** matriz;
    matriz=reservarMemoria(nFil, nCol);
    rellenaMatriz (matriz, nFil, nCol);
    imprimeMatriz(matriz, nFil, nCol);
    int* vector;
    vector=minCol(matriz, nFil, nCol);
    for(int i=0; i<nCol; i++){
        printf("%d   ", vector[i]);
    }
    printf("\n");

}
