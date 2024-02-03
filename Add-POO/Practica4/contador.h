/**
 * @file contador.h
 * @author Gonzalo Marquez (i02matog@uco.es)
 * @brief definition of the class Contador
 */

#ifndef CONTADOR_H
#define CONTADOR_H

#include <list>

class Contador{//Definición de la clase contador
    private:

        int valor_;//Valor actual del contador
        int min_;//Valor minimo del contador
        int max_;//Valor maximo del contador
        std::list<Contador> history_;//Historial de cambios
  
  /**
   * @brief función encargada de controlar que valor no supere los limites 
   */

        void controlValor();

    public:

          /**
           * @brief Construye un nuevo objeto de la clase contador
           * 
           * @param valor al que inicializamos el contador
           * @param min valor que puede tomar la variable valor
           * @param max valor que puede tomar la variable valor
           */
      
            Contador(int valor = 0, int min = 0, int max = 1000);

          /**
           * @brief iguala el valor del contador que la envia al entero n
           * 
           * @param n valor al que queremos igualar
           * @return contador con el nuevo valor
           */
      
          Contador operator=(const int &n);

          /**
           * @brief iguala el valor del contador que la envia al de otro contador
           * 
           * @param contador al que queremos igualar
           * @return Contador con los nuevos valores
           */
      
          Contador operator=(const Contador &contador);

          /**
           * @brief incrementa el valor del contador y lo devuelve incrementado
           * 
           * @return contador con el valor incrementado
           */
      
          Contador operator++(void);

          /**
           * @brief incrementa el valor pero lo devuelve sin incrementar
           * 
           * @return contador con el valor sin incrementar 
           */
      
          Contador operator++(int);

          /**
           * @brief decrementa el valor del contador y lo devuelve decrementado
           * 
           * @return contador con el valor decrementado
           */
      
          Contador operator--(void);

          /**
           * @brief decrementa el valor pero lo devuelve sin decrementar
           * 
           * @return contador con el valor sin decrementar 
           */
      
          Contador operator--(int);

          /**
           * @brief suma al valor del contador el entero pasado como argumento
           * 
           * @param n valor que queremos sumar al contador
           * @return contador con el valor sumado
           */
      
          Contador operator+(const int &n);

          /**
           * @brief suma al valor del contador el entero pasado como argumento
           * 
           * @param n valor que queremos sumar al contador
           * @return contador con el valor sumado
           */

          friend Contador operator+(const int &n, const Contador &contador);

          /**
           * @brief resta al valor del contador el entero pasado como argumento
           * 
           * @param n valor que queremos restar al contador
           * @return contador con el valor restado
           */
      
          Contador operator-(const int &n);

          /**
           * @brief resta al valor del contador el entero pasado como argumento
           * 
           * @param n valor que queremos restar al contador
           * @return contador con el valor restado
           */

          friend Contador operator-(const int &n, const Contador &contador);

          /**
           * @brief deshace tantos cambios como se le indique en el valor n pasado como parámetro. (Por defecto n = 1)
           * 
           * @param n de acciones que queremos deshacer
           * @return true si se ha podido volver a un estado anterior
           * @return false si no se ha podido volver a un estado anterior
           */

          bool undo(int const &n = 1);

          /**
           * @brief devuelve el valor actual de la variable valor
           * 
           * @return int con el valor actual de la variable
           */

          inline int get() const {return valor_;}
};


#endif