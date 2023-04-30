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
    void convertir_ieee(QString numero1, QString numero2);

    void convertir_exa(QString numero1, QString numero2);

    void suma();

    void multi();

    void div();
    //pasar ieee a hexa aqui

public:
    ALU();
};

#endif // ALU_H
