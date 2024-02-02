#ifndef CART_H
#define CART_H
#include "computer.h"
#include <iostream>
#include <list>
#include <fstream>

class Cart:public Computer{
    private:
        int ID_;
        std::list<Computer> clist;
    public:
        inline int getID(){return ID_;};
        inline int getN(){return clist.size();};
        inline void addComputer(Computer c){clist.push_back(c);};
        void print();
        void write();
};
#endif