/**
 * @file jugador.cc
 * @author Gonzalo Márquez (i02matog@uco.es)
 * @brief definition the methods of class Jugador
*/
#include "jugador.h"
#include <fstream>
#include <iostream>

void Jugador::setApuestas(){
	apuestas_.clear();//vaciamos la lista de apuestas
	std::ifstream f((getDNI()+".txt")); //se crea puntero para abrir el fichero en modo lectura mediante el nombre (DNI)
	if(!f){//Si no se abre correctamente, envia un error
		std::cout<<"Se ha producido un error al intentar abrir el fichero 'DNI.txt'\n";
		exit(EXIT_FAILURE);
	}
	Apuesta a; //Creacion de estructura temporal
	std::string cadena; 
	getline(f, cadena, ',');
	while(!f.eof()){ //Mediante el bucle se leera el fichero hasta el final
		a.tipo=std::stoi(cadena);
		getline(f, cadena, ',');
		a.valor=cadena;
		getline(f, cadena, '\n');
		a.cantidad=std::stoi(cadena);
		apuestas_.push_back(a);
		getline(f, cadena, ',');
	}
	f.close(); //Tras acabar la lectura del archivo, se cierra
}
