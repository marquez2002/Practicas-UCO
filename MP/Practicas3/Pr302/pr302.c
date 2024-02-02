#include "pr302.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fichero(char* nombre, int num, int min, int max){
    int aux=max-min;
    FILE* f1;
    srand(time(NULL));
    if((f1=fopen(nombre, "w"))==NULL){
        printf("ERROR al generar el archivo");
    }
    for(int i=0; i<num; i++){
        fprintf(f1, "%d\n", ((rand()%(aux))+min));
    }
    fclose(f1);
    printf("Todo correcto\n");
}