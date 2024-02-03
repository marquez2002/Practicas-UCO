/**
 * @file persona.h
 * @author Gonzalo Márquez (i02matog@uco.es)
 * @brief definition of the class Persona
*/

#ifndef PERSONA_H
#define PERSONA_H
#include <string>

class Persona{
private:
	std::string dni_; //dni persona
	std::string nombre_; //nombre persona
	std::string apellidos_; //apellidos persona
	int edad_;  //edad persona
	std::string direccion_; //direccion persona
	std::string localidad_; //localidad persona
	std::string provincia_; //provincia persona
	std::string pais_; //pais persona
public:

	/**
	 * @brief crea un objeto persona
	 * 
	 * @param dni persona(obligatorio)
	 * @param nombre persona(opcional)
	 * @param apellidos persona(opcional)
	 * @param edad persona(opcional)
	 * @param direccion persona(opcional)
	 * @param localidad persona(opcional)
	 * @param provincia persona(opcional)
	 * @param pais persona(opcional)
	*/

	Persona(std::string dni, std::string nombre="", std::string apellidos="", int edad=0, std::string direccion="", std::string localidad="", std::string provincia="", std::string pais="");

	/**
	 * @brief Asigna el dni a la persona
	 * 
	 * @param dni que se desea asignar a la persona
	*/

	inline void setDNI(std::string const dni) {dni_=dni;}

	/**
	 * @brief Devuelve el dni de la persona
	 * 
	 * @return std::string
	*/

	inline std::string getDNI() const{return dni_;}
	
	/**
	 * @brief Asigna el nombre a la persona
	 * 
	 * @param nombre que se desea asignar a la persona
	*/

	inline void setNombre(std::string const nombre) {nombre_=nombre;}

	/**
	 * @brief Devuelve el nombre de la persona
	 * 
	 * @return std::string
	*/

	inline std::string getNombre() const{return nombre_;}

	/**
	 * @brief Asigna los apellidos a la persona
	 * 
	 * @param apellidos que se desea asignar a la persona
	*/

	inline void setApellidos(std::string const apellidos){apellidos_=apellidos;}

	/**
	 * @brief Devuelve los apellidos de la persona
	 * 
	 * @return std::string
	*/

	inline std::string getApellidos() const {return apellidos_;}

	/**
	 * @brief Asigna la edad a la persona
	 * 
	 * @param edad que se desea asignar a la persona
	*/

	bool setEdad(int const &edad);

	/**
	 * @brief Devuelve la edad de la persona
	 * 
	 * @return std::int
	*/

	inline int getEdad() const{return edad_;}

	/**
	 * @brief Asigna el direccion a la persona
	 * 
	 * @param direccion que se desea asignar a la persona
	*/

	inline void setDireccion(std::string const direccion){direccion_=direccion;}

	/**
	 * @brief Devuelve la direccion de la persona
	 * 
	 * @return std::string
	*/

	inline std::string getDireccion() const{return direccion_;}

	/**
	 * @brief Asigna el localidad a la persona
	 * 
	 * @param localidad que se desea asignar a la persona
	*/

	inline void setLocalidad(std::string const localidad){localidad_=localidad;}

	/**
	 * @brief Devuelve la localidad de la persona
	 * 
	 * @return std::string
	*/
	inline std::string getLocalidad() const{return localidad_;}

	/**
	 * @brief Asigna el provincia a la persona
	 * 
	 * @param provincia que se desea asignar a la persona
	*/

	inline void setProvincia(std::string const provincia){provincia_=provincia;}

	/**
	 * @brief Devuelve la provincia de la persona
	 * 
	 * @return std::string
	*/

	inline std::string getProvincia() const{return provincia_;}

	/**
	 * @brief Asigna el pais a la persona
	 * 
	 * @param pais que se desea asignar a la persona
	*/

	inline void setPais(std::string const pais){pais_=pais;}

	/**
	 * @brief Devuelve el pais de la persona
	 * 
	 * @return std::string
	*/

	inline std::string getPais() const{return pais_;}

	/**
	 * @brief Concatena apellidos, nombre
	 * 
	 * @param dni que se desea asignar a la persona
	*/
	inline std::string getApellidosyNombre() const{return (apellidos_ + ", " + nombre_);}

	/**
	 * @brief Permite comprobar si una persona es mayor de edad
	 * 
	 * @return true si la persona es mayor de edad
	 * @return false si la persona no es mayor de edad
	*/

	bool mayor();
};

#endif