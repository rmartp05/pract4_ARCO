#include "alu.h"
#include "QString"
#include "sstream"

using namespace std;
ALU::ALU()
{
//real a ieee y ieee a hexa
}

    void ALU::convertir_ieee(QString numero1, QString numero2){
//si hago un switch porque en mainwindow le paso un 1 o 2 depende si es numero1 o numero2 y este metodo saca el numero q sea y alli lo guardo estaria bn? luego en este metodo
//llamo a hexa y alli hago lo mismo?

    union Code a;
    float num1 = numero1.toFloat();
    int sig1, exp1, frac1;
    a.numero = num1;
    sig1 = a.bitfield.sign;
    exp1 = a.bitfield.expo;
    frac1 = a.bitfield.partFrac;
    QString numero_1 = QString::number(sig1) + "." + QString::number(exp1) +QString::number(frac1);

    union Code b;
    float num2 = numero2.toFloat();
    int sig2, exp2, frac2;
    b.numero = num2;
    sig2 = b.bitfield.sign;
    exp2 = b.bitfield.expo;
    frac2 = b.bitfield.partFrac;
    QString numero_2 = QString::number(sig2) + "." + QString::number(exp2) +QString::number(frac2);

    convertir_exa(numero_1, numero_2);
    }

    void ALU::convertir_exa(QString numero_1, QString numero_2){

    }
