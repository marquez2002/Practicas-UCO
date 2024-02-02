#ifndef COMPUTER_H
#define COMPUTER_H

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
    };
#endif