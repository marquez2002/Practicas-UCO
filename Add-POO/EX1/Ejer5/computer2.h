#ifndef COMPUTER2_H
#define COMPUTER2_H
#include <iostream>

class Computer{
    private:
        std::string nombre_;
        std::string modelo_;
        int precio_;
    public:
        Computer(std::string nombre, std::string modelo, int precio=1);
        inline std::string getNombre(){return nombre_;};
        inline std::string getModelo(){return modelo_;};
        inline int getPrecio(){return precio_;};
        bool setNombre(std::string nombre);
        bool setModelo(std::string modelo);
        bool setPrecio(int precio);
        friend std::ofstream &operator<<(std::ofstream &stream, Computer &c);
        friend std::ifstream &operator>>(std::ifstream &stream, Computer &c);
    };
#endif