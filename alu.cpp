#include "alu.h"

#include "QString"
#include "sstream"
#include <bitset>
#include <string>
#include <iostream>
#include <climits>

using namespace std;

void ALU::leerOperadores(numero1, numero2)
{
    union Code a;
    a.numero = numero1.toFloat();
    // La asignacion de sign, expo y partFract es automatica segun se introduce la variable numero.
    operador1 = a; // Se guarda la conversion en la variable de clase para facilitar las posteriores operaciones.

    union Code b;
    b.numero = numero2.toFloat();
    operador2 = b; // Se guarda la conversion en la variable de clase para facilitar las posteriores operaciones.
}

void ALU::IeeeToHex()
{
    //convertir el ieee a hexa
    std::bitset<23> afrac(frac1);//todos son arrays falta juntarlos
    std::bitset<8> aexp(exp1);
    std::bitset<1> asig(sig1);

    std::bitset<24> bfrac(frac2);
    std::bitset<8> bexp(exp2);
    std::bitset<1> bsig(sig2);
}

void ALU::suma(QString numero1, QString numero2)
{
    //segun el pdf son 17 pasos y se le pasan los nums normales
    //se pasa los numeros a ieee
    // TIENES UNA FUNCION QUE CONVIERTE Y LO VUELVES HA HACER OTRA VEZ?

    int mantisa1 = exp1 | (1 << 23);//mueve el valor binario 1 a la izquierda 23 posiciones // ns si estara bn

    // TIENES UNA FUNCION QUE CONVIERTE Y LO VUELVES HA HACER OTRA VEZ?

    int mantisa2 = exp2 | (1 << 23);//mueve el valor binario 1 a la izquierda 23 posiciones // ns si estara bn

    //paso1
    int g, r, st;
    bool intercambio = false;
    bool completado_p = false;

    //paso2
    if(exp1 < exp2)
    {
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
    if(sig1 != sig2)
    {
        //mantisa2 = complemento_2(mantisa2)
        //QUE ES COMPLEMENTO_2
    }

    //paso5
    int P = mantisa2;//int no, tiene q ser un bitset para hacer el P(d-1)

    //paso6

    //paso7
    if(sig1 =! sig2)
    {
        int paso7 = (P >> d) | (1 << (sizeof(P) * 8 - 1 - d));
    }else
    {
        int resultado = (P >> d) | ((1 << d) - 1) << (sizeof(P) * 8 - d);
    }

    //paso8
    P = mantisa1 + P;
    int c1;//el acarreo como se hace?


}

