#include "alu.h"
#include "QString"
#include "sstream"
#include <bitset>
#include <string>
#include <iostream>
#include <climits>

using namespace std;
ALU::ALU()
{
//real a ieee y ieee a hexa
}

    void ALU::convertir(QString numero1, QString numero2, int opc){
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

    //convertir el ieee a hexa
    std::bitset<23> afrac(frac1);//todos son arrays falta juntarlos
    std::bitset<8> aexp(exp1);
    std::bitset<1> asig(sig1);

    std::bitset<24> bfrac(frac2);
    std::bitset<8> bexp(exp2);
    std::bitset<1> bsig(sig2);

    //teniendolo todo hay que ingeniarselas para q este todo junto en un QString y q los mande al mainwindow (con un switch?) para ponerlos en el ui.
    }

    void ALU::suma(QString numero1, QString numero2){//segun el pdf son 17 pasos y se le pasan los nums normales
    //se pasa los numeros a ieee
    union Code a;
    float num1 = numero1.toFloat();
    int sig1, exp1, frac1;
    a.numero = num1;
    sig1 = a.bitfield.sign;
    exp1 = a.bitfield.expo;
    frac1 = a.bitfield.partFrac;
    QString numero_1 = QString::number(sig1) + "." + QString::number(exp1) +QString::number(frac1);
    int mantisa1 = exp1 | (1 << 23);//mueve el valor binario 1 a la izquierda 23 posiciones // ns si estara bn


    union Code b;
    float num2 = numero2.toFloat();
    int sig2, exp2, frac2;
    b.numero = num2;
    sig2 = b.bitfield.sign;
    exp2 = b.bitfield.expo;
    frac2 = b.bitfield.partFrac;
    QString numero_2 = QString::number(sig2) + "." + QString::number(exp2) +QString::number(frac2);
    int mantisa2 = exp2 | (1 << 23);//mueve el valor binario 1 a la izquierda 23 posiciones // ns si estara bn
    //paso1
    int g, r, st;
    bool intercambio = false;
    bool completado_p = false;
    //paso2
    if(exp1 < exp2){
        QString aux;
        aux = numero1;
        numero1 = numero2;
        numero2 = aux;
        intercambio = true;
    }
    //paso3
    int expsuma = exp1;
    int d = exp1 - exp2;
    //paso4
    if(sig1 != sig2){
        //mantisa2 = complemento_2(mantisa2)
        //QUE ES COMPLEMENTO_2
    }
    //paso5
    int P = mantisa2;//int no, tiene q ser un bitset para hacer el P(d-1)
    //paso6

    //paso7
    if(sig1 =! sig2){
        int paso7 = (P >> d) | (1 << (sizeof(P) * 8 - 1 - d));
    }else{
        int resultado = (P >> d) | ((1 << d) - 1) << (sizeof(P) * 8 - d);
    }
    //paso8
    P = mantisa1 + P;
    int c1;//el acarreo como se hace?


    }
