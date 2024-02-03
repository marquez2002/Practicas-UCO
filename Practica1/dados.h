/**
 * @file dados.h
 * @author Gonzalo Márquez (i02matog@uco.es)
 * @brief definition of the class Dados
*/

#ifndef dados_h
#define dados_h
#include <vector>

class Dados{
private:
	int d1_; //Dado 1
	int d2_; //Dado 2

	int l1_; //Numero de lanzamiento dado1
	int l2_; //Numero de lanzamiento dado2

	int sum1_; //Suma valores obtenidos de los lanzaminetos del dado1
	int sum2_; //Suma valores obtenidos de los lanzaminetos del dado2

	std::vector <int> v1; //Vector que almacena los 5 ultimos valores del dado1
	std::vector <int> v2; //Vector que almacena los 5 ultimos valores del dado2

	/**
	* @brief Añade el último valor del dado1
	* 
	* @return void
	*/

	void ordena1();

	/**
	* @brief Añade el último valor del dado2
	* 
	* @return void
	*/

	void ordena2();

public:

	/**
	*@brief crea un nuevo objeto dados
	*/

	Dados();

	/**
	* @brief Lanza los dados
	* 
	* @return void
	*/

	void lanzamiento();

	/**
	* @brief Devuelve el valor del dado1
	* 
	* @return int
	*/

	inline int getDado1() const {return d1_;}

	/**
	* @brief Devuelve el valor del dado2
	* 
	* @return int
	*/

	inline int getDado2() const {return d2_;}

	/**
	* @brief Asigna un valor al dado1
	* 
	* @param int v que se desea asignar al dado1
	* @return true si se ha podido asignar el valor
	* @return false si no se ha podido asignar el valor
	*/

	bool setDado1(const int &v);

	/**
	* @brief Asigna un valor al dado2
	* 
	* @param int v que se desea asignar al dado2
	* @return true si se ha podido asignar el valor
	* @return false si no se ha podido asignar el valor
	*/

	bool setDado2(const int &v);

	/**
	* @brief Devuelve el valor de sumar el dado1 con el dado2
	* 
	* @return int
	*/

	inline int getSuma() const {return (d1_+d2_);}

	/**
	* @brief Devuelve el valor de restar el dado1 con el dado2
	* 
	* @return int
	*/

	int getDiferencia() const;

	/**
	* @brief Devuelve el numero de lanzamientos del dado1
	* 
	* @return int
	*/

	inline int getLanzamientos1() const {return l1_;};

	/**
	* @brief Devuelve el numero de lanzamientos del dado2
	* 
	* @return float
	*/

	inline int getLanzamientos2() const {return l2_;};

	/**
	* @brief Devuelve la media de los valores del dado1
	* 
	* @return float
	*/

	float getMedia1() const;
	
	/**
	* @brief Devuelve la media de los valores del dado2
	* 
	* @return float
	*/

	float getMedia2() const;
	
	/**
	* @brief Copia en el vector pasado como parámetro, los últimos 5 valores del dado1
	* 
	* @param vector de enteros
	* @return void
	*/

	void getUltimos1(int ultimos[]) const;

	/**
	* @brief Copia en el vector pasado como parámetro, los últimos 5 valores del dado2
	* 
	* @param vector de enteros
	* @return void
	*/

	void getUltimos2(int ultimos[]) const;
};

#endif