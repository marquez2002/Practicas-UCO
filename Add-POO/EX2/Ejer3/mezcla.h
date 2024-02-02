#ifndef MEZCLA_H
#define MEZCLA_H
#include "tarea.h"
#include <list>

class Mezcla:public Tarea{
    private:
        std::list<std::string> lista;
    public:
        inline Mezcla(int ID, std::string nombre):Tarea(ID, nombre){};
        inline int getN(){lista.size();};
        bool addIngrediente();
        void print();
        void write();

};
#endif