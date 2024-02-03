#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float norma(float x[], float valores_iniciales[], int dimension){
	float norma=0;
	for(int i=1; i<dimension;i++){
		norma=norma+((x[i])-(valores_iniciales[i]))*(x[i]-valores_iniciales[i]);
	}
	return norma;
}

float sumagaussseidel(float* auxiliar, float valores_iniciales[], int i, int dimension){
	float suma=0;
	for(int j=1; j<dimension; j++){
		if(i!=j){
			suma=suma+auxiliar[i]*valores_iniciales[i];
		}
	}
	return suma;
}

int main(){
	system("clear");
	int m, n;
	float criterioparada, error;
	printf("Para la empleacion del metodo de Jacobi tendremos que tener un sistema de tipo A·x=b\n");			
	int dimension, iteracion;
	/* Introducimos todas las variables*/
	printf("En primer lugar deberemos de conocer la dimension de la matriz a fin de crear la distintas matrices\n");
	scanf("%d", &dimension);
	dimension=dimension-1;
	/*Pedimos la dimension de la matriz a crear */
	printf("Creando la matriz A\n");
	float A[dimension][dimension];
	printf("Introduzca los valores de la matriz A\n");
	/* Introducimos los valores de la matriz A*/
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			printf("\nA[%d][%d]=", i, j);
			scanf("%f", &A[i][j]);
		}
	}

	printf("Creando el vector x\n");
	float x[dimension];
	/* Creamos el vector x */

	printf("Creando el vector b\n");
	float b[dimension];
	printf("Introduzca los valores del vector b\n");
	/* Introducimos los valores pertencientes a b */
	for(int i=0; i<dimension; i++){
		printf("\nA[%d]=", i);
		scanf("%f", &b[i]);
	}

	printf("\n Error de parada: E=\n");
	/* Introducimos el criterio de parada*/
	scanf("%f", &criterioparada);
	error=criterioparada+1; /* Ponemos que el error sea mayor que criterio de parada para poder entrar en el while*/

	float valores_iniciales[dimension], auxiliar[dimension];
	printf("Los valores iniciales de la iteracion seran: \n");
	/* Introducimso el vector con los valores iniciales */
	for(int i=0; i<dimension;i++){
			printf("x0(%d)=", i);
			scanf("%f", &valores_iniciales[i]);
	}
	
	while(error>criterioparada){
		for(int i=1; i<dimension;i++){
					x[0]=(b[0]+A[i][1]*valores_iniciales[1]+A[i][2]*valores_iniciales[2])/valores_iniciales[0];
					x[1]=(b[1]+A[i][0]*valores_iniciales[0]+A[i][2]*valores_iniciales[2])/valores_iniciales[1];
					x[2]=(b[2]+A[i][0]*valores_iniciales[0]+A[i][1]*valores_iniciales[1])/valores_iniciales[2];
					/*Calculamos los valores de la solucion uno por uno como en el ejemplo del pdf*/
		
			printf("\n Iteracion %d: \n", iteracion);
			for(int i=1; i<=dimension;i++){
				/* Contamos la iteraciones necesarias para ir realizando el proceso */
				valores_iniciales[i]=x[i];
				printf("X(%d)=%f \n",i, x[i]);
			}
			iteracion++;
		}
		error=norma(x, valores_iniciales, dimension);
		for(int i=1; i<dimension;i++){
			/* Pasamos los valores de x a los valores iniciales para poder seguir realizando el proceso y obtener la solucion*/
			valores_iniciales[i]=x[i];
		}

		if(iteracion==20){
			/* Saldremos del codigo si se necesitan mas de 20 iteraciones*/
			error=criterioparada-1;
		}
	}

	printf("Solucion del sistema: \n");
	/* Imprimimos por pantalla la solucion del sistema*/
	printf("El numero de iteraciones ha sido de %d\n", iteracion);
	for(int i=1; i<=dimension;i++){
		printf("X(%d)=%f \n",i, x[i]);
	}
	return 1;
}



	