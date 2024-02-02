#ifndef CONTADOR_H
#define CONTADOR_H

class Contador{
    private:
        int valor_;
        int maximo_;
    public:
        Contador(int valor=0, int maximo=100);
        inline int getV(){return valor_;}
        inline int getM(){return maximo_;}
        bool setV(int valor);
        bool setM(int maximo);
        Contador operator=(int valor);
        Contador operator=(Contador a);
        Contador operator++(void);
        Contador operator++(int);
        Contador operator+(int a);
        friend Contador operator+(int aux, Contador a);
};
#endif