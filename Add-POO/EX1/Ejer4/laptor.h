#ifndef LAPTOR_H
#define LAPTOR_H
#include "computer.h"
#include <iostream>

class Laptor:public Computer{
    private:
        int pulgadas_;
    public:
        Laptor(int pulgadas, std::string modelo, int precio);
        inline int getPulgadas(){return pulgadas_;};
        bool setPulgadas(int pulgadas);
        inline void getInfo(){std::cout<<"Laptor de " + std::to_string(getPulgadas())+" de "+ (getModelo()) + " de " + std::to_string(getPrecio())<<"\n";};
};  
#endif