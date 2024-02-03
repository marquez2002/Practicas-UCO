/**
 * @file persona.h
 * @author Gonzalo Márquez (i02matog@uco.es)
 * @brief definition of the methods of the class Persona
*/
#include "persona.h"

Persona::Persona(std::string dni, std::string nombre, std::string apellidos, int edad, std::string direccion, std::string localidad, std::string provincia, std::string pais){
	dni_=dni; //Asignamos el valor dni al dni correspondiente de la persona
	nombre_=nombre; ////Asignamos el valor nombre al nombre correspondiente de la persona
	apellidos_=apellidos; ////Asignamos el valor apellidos a los apellidos correspondiente de la persona
	edad_=edad; ////Asignamos el valor edad a la edad correspondiente de la persona
	direccion_=direccion; ////Asignamos el valor direccion a la direccion correspondiente de la persona
	localidad_=localidad; ////Asignamos el valor localidad a la localidad correspondiente de la persona
	provincia_=provincia; ////Asignamos el valor provincia a la provincia correspondiente de la persona
	pais_=pais; ////Asignamos el valor pais al pais correspondiente de la persona
}

bool Persona::setEdad(int const &edad){
	if(edad>=0){//Comprueba que la edad sea mayor que 0
		edad_=edad;
		return true;
	}
	return false;
}

bool Persona::mayor(){
	if(getEdad()>=18){//Comprueba con la edad de la persona es mayor de 18
		return true;
	}
	return false;
}