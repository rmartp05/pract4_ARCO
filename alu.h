#ifndef ALU_H
#define ALU_H

#include "QString"
#include "sstream"
#include "bitset"

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

    void multi();

    void div();
    void ieeeToHex();
    void imprimirNumeroBinario(float numero);
    bitset<24> convertBinary(bitset<24> mantisa);
    bitset<24> calcularComplementoDos(bitset<24> numero);
    bitset<24> calcular_acarreo(bitset<24> a, bitset<24> b);
    string floatToBinaryIEEE754(float value);

    // pasar ieee a hexa aqui

public:
    ALU();

    void leerOperadores(QString numero1, QString numero2);

    void suma();
};

#endif // ALU_H
