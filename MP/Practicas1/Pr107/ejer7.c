#include "ejer7.h"
#include <math.h>



void estadisticasVector(int a[], int n, int* media, int* varianza, int* desviacion_tip){
    int suma=0, suma2=0;
    for(int i=0; i<n; i++){
        suma+=a[i];
        suma2+=pow(a[i], 2);
    }
    *media=(suma/n);
    *varianza=(suma2/n)-pow(*media, 2);
    *desviacion_tip=sqrt(*varianza);
}