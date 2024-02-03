/**
 * @file ruleta.h
 * @author Gonzalo Márquez (i02matog@uco.es)
 * @brief definition of the class Ruleta
*/

#ifndef RULETA_H
#define RULETA_H
#include <list>
#include "crupier.h"
#include "jugador.h"



class Ruleta{//Definicion de la clase Ruleta
private:
	int banca_; //Dinero de la banca
	int bola_; //Numero en el que ha caido la bola
	std::list<Jugador> jugadores_; //Lista de jugadores 
	Crupier crupier_; //Crupier encargado

public:

	/**
	 * @brief crea un objeto ruleta
	 * 
	 * @param crupier encargado de la ruleta
	*/

	inline Ruleta(Crupier const &crupier) : crupier_(crupier.getDNI(), crupier.getCodigo()){srand(time(NULL)); banca_=1000000; bola_=-1;}


	/**
	 * @brief Modifica el saldo de la banca
	 * 
	 * @param saldo a asignar
	 * @return true si se ha asignado
	 * @return false si no se ha asignado
	*/


	bool setBanca(int const &banca);

	/**
	 * @brief Devuelve el dinero de la banca
	 * 
	 * @return int
	*/

	inline int getBanca() const{return banca_;};

	/**
	 * @brief Modifica el valor de la bola
	 * 
	 * @param valor de la bola de la ruleta
	 * @return true si se ha asignado
	 * @return false si no se ha asignado
	*/

	bool setBola(int const &bola);

	/**
	 * @brief Devuelve el valor de la bola
	 * 
	 * @return int
	*/

	inline int getBola() const{return bola_;};

	/**
	 * @brief Asigna el crupier de la ruleta
	 * 
	 * @param crupier que se desea asignar
	 * @return void
	*/

	inline void setCrupier(Crupier const &crupier){crupier_=crupier;};

	/**
	 * @brief Devuelve el crupier de la ruleta
	 * 
	 * @return Crupier
	*/

	inline Crupier getCrupier() const{return crupier_;};

	/**
	 * @brief Devuelve una lista con los jugadores que se encuentran jugando en la ruleta
	 * 
	 * @return std::list<Jugadores>
	*/

	inline std::list<Jugador> getJugadores() const{return jugadores_;};

	/**
	 * @brief Añade el jugador pasado como parametro a la ruleta 
	 * 
	 * @param jugador que se desea añadir
	 * @return true si se ha podido añadir
	 * @return false si no se ha podido añadir
	*/

	bool addJugador(Jugador &jugador);

	/**
	 * @brief borra el jugador pasado como parametro 
	 * 
	 * @param jugador que se desea eliminar
	 * @return 1 si se ha podido eliminar
	 * @return -1 si la lista de jugadores esta vacia
	 * @return -2 si el jugador no se encuentra en la lista
	*/

	int deleteJugador(std::string const &dni);

	/**
	 * @brief borra el jugador pasado como parametro 
	 * 
	 * @param dni del jugador que se desea eliminar
	 * @return 1 si se ha podido eliminar
	 * @return -1 si la lista de jugadores esta vacia
	 * @return -2 si el jugador no se encuentra en la lista
	*/

	int deleteJugador(Jugador &jugador);

	/**
	 * @brief lee los datos de la lista de jugadores en jugadores.txt y los pasa a la lista jugadores_
	 * 
	 * @return void
	*/

	void leeJugadores();

	/**
	 * @brief escribe los datos de la lista de jugadores en jugadores.txt 
	 * 
	 * @return void
	*/

	void escribeJugadores();

	/**
	 * @brief simula el lanzamineto de la bola en la ruleta devolviendo un numero aleatorio entre 1-36
	 * 
	 * @return void
	*/

	inline void giraRuleta(){setBola(((rand()%37)));};

	/**
	 * @brief se ejecuta despues de cada tirada y se encarga de actualizar el saldo de la banca y del jugador
	 * 
	 * @return void
	*/

	void getPremios();

	/**
	 * @brief comprueba si el jugador ha acertado el color
	 * 
	 * @param color al que ha apostado el jugador
	 * @return true si ha acertado
	 * @return false si ha fallado
	*/

	bool aciertaColor(std::string const &color);

	/**
	 * @brief comprueba si el jugador ha acertado su paridad
	 * 
	 * @param paridad al que ha apostado el jugador
	 * @return true si ha acertado
	 * @return false si ha fallado
	*/

	bool aciertaParidad(std::string const &paridad);

	/**
	 * @brief comprueba si el jugador ha acertado su zona
	 * 
	 * @param color al que ha apostado el jugador
	 * @return true si ha acertado
	 * @return false si ha fallado
	*/

	bool aciertaZona(std::string const &zona);
};
#endif