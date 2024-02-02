#ifndef TAREA_H
#define TAREA_H
#include <iostream>

class Tarea{
    private:
        std::string nombre_;
        int ID_;
    public:
        Tarea(int ID, std::string nombre="XX");
        inline int getID(){return ID_;};
        inline std::string getNombre(){return nombre_;};
        bool setNombre(std::string nombre);
        bool setID(int ID);
};
#endif