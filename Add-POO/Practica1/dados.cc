/**
 * @file dados.cc
 * @author Gonzalo Márquez (i02matog@uco.es)
 * @brief body of the methods of the class Dados
*/
#include <cstdlib>
#include <ctime>
#include "dados.h"


Dados::Dados(){
	srand(time(NULL));
	d1_=1; //valor por defecto del dado1
	d2_=1; //valor por defecto del dado2
	l1_=0; //ponemos a 0 el lanzamiento del dado1
	l2_=0; //ponemos a 0 el lanzamiento del dado2
	sum1_=0; //ponemos a 0 la suma de valores del dado1
	sum2_=0; //ponemos a 0 la suma de valores del dado1
	v1.resize(5,0); //ponemos a 0 el vector de los ultimos 5 lanzamientos del dado1
	v2.resize(5,0); //ponemos a 0 el vector de los ultimos 5 lanzamientos del dado1
}


void Dados::lanzamiento(){
	setDado1(((rand()%6)+1)); //valor aleatorio para el dado1 entre 1 y 7
	setDado2(((rand()%6)+1)); //valor aleatorio para el dado2 entre 1 y 7
}

bool Dados::setDado1(const int &v){
	if(v>0 && v<7){ //comprobacion de que el valor a asignar al dado1 se encuentra entre 1 y 7
		d1_=v; //asignacion a dado1
		l1_++; //incrementa el numero de lanzamientos del dado1
		sum1_+=getDado1(); //se añade a la suma al sumatorio de valores del dado1
		ordena1(); //actualizacion del vector de los ultimos 5 valores del dado1
		return true;
	}
	return false;
}

bool Dados::setDado2(const int &v){
	if(v>0 && v<7){ //comprobacion de que el valor a asignar al dado2 se encuentra entre 1 y 7
		d2_=v; //asignacion a dado2
		l2_++; //incrementa el numero de lanzamientos del dado2
		sum2_+=getDado2(); //se añade a la suma al sumatorio de valores del dado2
		ordena2(); //actualizacion del vector de los ultimos 5 valores del dado2
		return true;
	}
	return false;
}

int Dados::getDiferencia() const{
	return (abs(d1_-d2_)); //retorno de la resta de los valores del dado1 y dado2
}

float Dados::getMedia1() const{
	float media=0;
	if(l1_==0){ //si el lanzamiento es 0 se devuelve media=0
		return media;
	}
	media=((float)sum1_/(float)l1_); //si el lanzamiento es distinto de 0 se devuelve la media correspondiente del dado1
	return media;
}

float Dados::getMedia2() const{
	float media=0;
	if(l2_==0){//si el lanzamiento es 0 se devuelve media=0
		return media;
	}
	media=((float)sum2_/(float)l2_); //si el lanzamiento es distinto de 0 se devuelve la media correspondiente del dado2
	return media;
}


void Dados::ordena1(){ //Se mueve el vector uan posicion a la derecha y borra el ultimo elemento para incluir el siguiente valor
	v1.emplace(v1.begin(), getDado1());
	v1.pop_back();
}

void Dados::ordena2(){ //Se mueve el vector uan posicion a la derecha y borra el ultimo elemento para incluir el siguiente valor
	v2.emplace(v2.begin(), getDado2());
	v2.pop_back();
}

void Dados::getUltimos1(int ultimos[]) const{ //Copia en el vector pasado como parámetro, los últimos 5 valores del dado1
	for(int i=0; i<5; i++){
		ultimos[i]=v1[i];
	}
}

void Dados::getUltimos2(int ultimos[]) const{ //Copia en el vector pasado como parámetro, los últimos 5 valores del dado2
	for(int i=0; i<5; i++){
		ultimos[i]=v2[i];
	}
}