#ifndef ALU_H
#define ALU_H

#include "QString"
#include "sstream"

using namespace std;

class ALU
{
private:
    union Code {

        struct{
            unsigned int partFrac : 23;
            unsigned int expo : 8;
            unsigned int sign : 1;
        }bitfield;

        float numero;
        unsigned int numerox;
    };

    union Code operador1;
    union Code operador2;

    unsigned int hexNumA;
    unsigned int hexNumB;

    void suma(QString numero1, QString numero2);

    void multi();

    void div();
    void ieeeToHex();

    // pasar ieee a hexa aqui

public:
    ALU();

    void leerOperadores(QString numero1, QString numero2);

};

#endif // ALU_H