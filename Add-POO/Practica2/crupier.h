/**
 * @file cruppier.h
 * @author Gonzalo Márquez (i02matog@uco.es)
 * @brief definition of the class Crupier
*/
#ifndef CRUPIER_H
#define CRUPIER_H
#include "persona.h"

class Crupier: public Persona{//definicion de la clase crupier que hereda los atributos de la clase persona
private:
	std::string codigo_; //codigo del crupier
public:

	/**
	 * @brief crea un objeto crupier
	 * 
	 * @param dni persona(obligatorio)
	 * @param codigo crupier(obligatorio)
	 * @param nombre persona(opcional)
	 * @param apellidos persona(opcional)
	 * @param edad persona(opcional)
	 * @param direccion persona(opcional)
	 * @param localidad persona(opcional)
	 * @param provincia persona(opcional)
	 * @param pais persona(opcional)
	*/

	inline Crupier(std::string dni, std::string codigo, std::string nombre="", std::string apellidos="", int edad=0, std::string direccion="", std::string localidad="", std::string provincia="", std::string pais="") : Persona(dni, nombre, apellidos, edad, direccion, localidad, provincia, pais){codigo_=codigo;}

	/**
	 * @brief Asigna un codigo al empleado
	 * 
	 * @return std::string
	*/

	inline void setCodigo(std::string const codigo){codigo_=codigo;}

	/**
	 * @brief Devuelve el codigo del crupier
	 * 
	 * @return void
	*/

	inline std::string getCodigo() const{return codigo_;}
};
#endif
