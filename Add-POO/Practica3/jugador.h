/**
 * @file jugador.h
 * @author Gonzalo Márquez (i02matog@uco.es)
 * @brief definition of the class Jugador
*/

#ifndef JUGADOR_H
#define JUGADOR_H
#include "persona.h"
#include <list>

struct Apuesta{ //Estructura apuesta en funcion de la lista apuestas
	int tipo;
	std::string valor;
	int cantidad;
};

class Jugador: public Persona{ //definicion de la clase jugador que hereda los atributos de la clase persona
private:
	int dinero_; //Dinero jugador
	std::string codigo_; //Codigo jugador
	std::list<Apuesta> apuestas_; //Lista que tiene las apuestas del jugador

public:

	/**
	 * @brief crea un objeto jugador
	 * 
	 * @param dni persona(obligatorio)
	 * @param codigo persona(obligatorio)
	 * @param nombre persona(opcional)
	 * @param apellidos persona(opcional)
	 * @param edad persona(opcional)
	 * @param direccion persona(opcional)
	 * @param localidad persona(opcional)
	 * @param provincia persona(opcional)
	 * @param pais persona(opcional)
	*/

	inline Jugador(std::string dni, std::string codigo, std::string nombre="", std::string apellidos="", int edad=0, std::string direccion="", std::string localidad="", std::string provincia="", std::string pais="") : Persona(dni, nombre, apellidos, edad, direccion, localidad, provincia, pais){codigo_=codigo; dinero_=1000;}

	/**
	 * @brief Asigna un codigo al jugador
	 * 
	 * @return std::void
	*/

	inline void setCodigo(std::string codigo){codigo_=codigo;}

	/**
	 * @brief Devuelve un codigo al jugador
	 * 
	 * @return std::string
	*/

	inline std::string getCodigo(){return codigo_;}

	/**
	 * @brief Asigna dinero al jugador
	 * 
	 * @return std::void
	*/

	inline void setDinero(int dinero){dinero_=dinero;}

	/**
	 * @brief Devuelve el dinero al jugador
	 * 
	 * @return int
	*/

	inline int getDinero(){return dinero_;}

	/**
	 * @brief Devuelve la lista con las apuestas del jugador
	 * 
	 * @return std::list<Apuestas>
	*/

	inline std::list<Apuesta> getApuestas(){return apuestas_;}

	/**
	 * @brief Permite asignar una lista de apuestas al jugador a partir de un fichero de texto
	 * 
	 * @return void
	*/

	void setApuestas();
};

#endif
