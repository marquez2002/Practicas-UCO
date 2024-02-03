/**
 * @file contador.cc
 * @author Gonzalo Marquez (i02matog@uco.es)
 * @brief definition of the methods of the class Contador
 */
 
#include "contador.h"
#include <iostream>

Contador::Contador(int valor, int min, int max)
{
  if (valor<min || valor>max || min>max){//El valor se encuentra dentro de los limites
    valor=0;
    min=0;
    max=1000;
  }
  valor_=valor;//Asignar el valor pasado como parámetro 
  min_=min;//Asignar el valor pasado como parámetro 
  max_=max;//Asignar el valor pasado como parámetro 
  history_.push_back(*this);//Se introducen los cambios
}

void Contador::controlValor()
{
  if (valor_>max_){//Comprobamos que el valor no supera el limite superior
    valor_=max_;
  }
  else if(valor_<min_){//Comprobamos que el valor no supera el limite inferior
    valor_=min_;
  }
  history_.push_back(*this);//Se introducen los cambios
}

Contador Contador::operator=(const int &n){
  this->valor_= n;//Asignamos un valor
  controlValor();//Comprobamos que no se hayan excedido los limites del intervalo y guardamos el cambio
  return *this;
}

Contador Contador::operator=(const Contador &contador){
  this->valor_ = contador.valor_;//Asignamos el valor
  this->min_ = contador.min_;//Asignamos el valor
  this->max_ = contador.max_;//Asignamos el valor
  this->history_ = contador.history_;//Copiamos el historial de cambios
  history_.push_back(*this);//Comprobamos que no se superen los limites del intervalo y guardamos el cambio 
  return *this;
}

Contador Contador::operator++(void){
  ++this->valor_;//Incrementamos el valor
  controlValor();//Comprobamos que no se superen los limites del intervalo y guardamos el cambio
  return *this;
}

Contador Contador::operator++(int){
  Contador aux = *this;//Copiamos los valores actuales del puntero a uno auxiliar
  ++this->valor_;//Incrementamos el valor del contador actual
  controlValor();//Comprobamos que no se superan los limites del intervalo y guardamos el cambio en el historial del contador actual
  return aux;
}

Contador Contador::operator--(){
  --this->valor_;//Decrementamos el valor
  controlValor();//Comprobamos que no se superan los limites del intervalo y guardamos el cambio
  return *this;
}

Contador Contador::operator--(int){
  Contador aux = *this;//Copiamos los valores actuales del puntero a uno auxiliar
  --this->valor_;//Decrementamos el valor del contador
  controlValor();//Comprobamos que no se superen los limites del intervalo y guardamos el cambio en el historial
  return aux;
}

Contador Contador::operator+(const int &n){
  this->valor_ += n; //Le sumamos al valor actual el de n que ha sido pasado como parametro
  controlValor();//Comprobamos que no se superen los limites del intervalo y guardamos el cambio en el historial
  return *this;
}

Contador operator+(const int &n, const Contador &contador){
  Contador aux;//Creamos un contador
  aux.valor_ = n + contador.valor_;//Guardamos el nuevo valor en el contador auxiliar
  aux.max_ = contador.max_;//Guardamos el nuevo valor en el contador auxiliar
  aux.min_ = contador.min_;//Guardamos el nuevo valor en el contador auxiliar
  aux.controlValor();//Comprobamos que no se superado los limites del intervalo y guardamos el cambio
  return aux;
}

Contador Contador::operator-(const int &n){
  this->valor_ -= n; //Le restamos al valor actual el de n que ha sido pasado como parametro
  controlValor();//Comprobamos que no se superado los limites del intervalo y guardamos el cambio
  return *this;
}

Contador operator-(const int &n, const Contador &contador){
  Contador aux;//Creamos un contador
  aux.valor_ = n - contador.valor_;//Guardamos el nuevo valor en el contador auxiliar
  aux.max_ = contador.max_;//Guardamos el nuevo valor en el contador auxiliar
  aux.min_ = contador.min_;//Guardamos el nuevo valor en el contador auxiliar
  aux.controlValor();//Comprobamos que no se superado los limites del intervalo y guardamos el cambio
  return aux;
}

bool Contador::undo(int const &n){
  if (n >= (int) history_.size() || n<1){//Comprobamos que haya elementos suficientes en el historial para volver hacia atrás y que n sea mayor que 1.
    return false;
  }
  for (int i = 0; i < n; i++){//Vamos eliminando del historial hasta llegar a la posición que queríamos
    history_.pop_back();//Borramos
  } 
  *this = history_.back();//Actualizamos el valor del puntero al actual con los cambios deshechos
  return true; 
}