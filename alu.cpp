#include "alu.h"

#include "QString"
#include "sstream"
#include <bitset>
#include <string>
#include <iostream>
#include <climits>

using namespace std;

ALU::ALU() {
    // código para inicializar la clase ALU
}

void ALU::leerOperadores(QString numero1, QString numero2)
{
    union Code a;
    a.numero = numero1.toFloat();
    // La asignacion de sign, expo y partFract es automatica segun se introduce la variable numero.
    this->operador1 = a; // Se guarda la conversion en la variable de clase para facilitar las posteriores operaciones.

    union Code b;
    b.numero = numero2.toFloat();
    this->operador2 = b; // Se guarda la conversion en la variable de clase para facilitar las posteriores operaciones.

    std::bitset<23> pf(a.bitfield.partFrac);
    std::bitset<8> e(a.bitfield.expo);
    std::bitset<1> s(a.bitfield.sign);

    imprimirNumeroBinario(41);

    std::cout << "Parte fraccionaria: " << pf << std::endl;
    std::cout << "Exponente: " << e << std::endl;
    std::cout << "Signo: " << s << std::endl;
}

void ALU::imprimirNumeroBinario(float numero)
{
    union Code a;
    a.numero = numero;
    bitset<32> b = *reinterpret_cast<bitset<32>*>(&a.numerox);
    cout << "Número en punto flotante: " << a.numero << endl;
    cout << "Representación binaria: " << b << endl;
}

void ALU::ieeeToHex()
{
    bitset<23> afrac(operador1.bitfield.partFrac);
    bitset<8> aexp(operador1.bitfield.expo);
    bitset<1> asig(operador1.bitfield.sign);

    this->hexNumA = ((asig.to_ulong() << 31) | (aexp.to_ulong() << 23) | afrac.to_ulong());

    bitset<24> bfrac(operador2.bitfield.partFrac);
    bitset<8> bexp(operador2.bitfield.expo);
    bitset<1> bsig(operador2.bitfield.sign);

    this->hexNumB = ((bsig.to_ulong() << 31) | (bexp.to_ulong() << 23) | bfrac.to_ulong());
}

//void ALU::suma()
//{

//    int mantisa1 = operador1.bitfield.expo | (1 << 23); //mueve el valor binario 1 a la izquierda 23 posiciones
//    int mantisa2 = operador2.bitfield.expo | (1 << 23); //mueve el valor binario 1 a la izquierda 23 posiciones

//    //paso1
//    bitset<24> P;
//    int g, r, st = 0;
//    int n = 24; // Numero de bits de la mantisa
//    bool intercambio = false;
//    bool completado_P = false;

//    //paso2
//    if(operador1.bitfield.expo < operador2.bitfield.expo)
//    {
//        union Code aux;
//        aux = operador1;
//        operador1 = operador2;
//        operador2 = aux;
//        intercambio = true;
//    }

//    //paso3
//    union Code suma;
//    suma.bitfield.expo = operador1.bitfield.expo;
//    int d = operador1.bitfield.expo - operador2.bitfield.expo;

//    if(d<0)
//    {
//        // ERROR
//    }

//    //paso4
//    if(operador1.bitfield.sign != operador2.bitfield.sign)
//    {
//        mantisa2 = ~mantisa2 + 1;
//    }

//    //paso5
//    P = mantisa2;

//    //paso6
//    // d=0 -> nada d=1->g d=2->g,r d=3 -> g,r y st st->mirar hasta el final si hay un 1
//    if (P[23]) {
//        g = P[24];
//        r = P[23];
//    }
//    for (int i = 22; i >= 0; --i) {
//        if (P[i]) {
//            st = 1;
//            break;
//        }
//    }

//    //paso7
//    if(operador1.bitfield.sign =! operador2.bitfield.sign)
//    {
//        P = (P >> d) | (1 << (sizeof(P) * 8 - 1 - d));
//    }else
//    {
//        P = (P >> d) | ((1 << d) - 1) << (sizeof(P) * 8 - d);
//    }

//    //paso8

//    P = mantisa1 + P;
//    C = calcular_acarreo(mantisa1, P);

//    // paso9
//    if((operador1.bitfield.sign != operador2.bitfield.sign) && (P[n-1] == 1) && (C = 0))
//    {
//        P = ~P + 1;
//        completado_P = true;
//    }

//    // paso10
//    if((operador1.bitfield.sign == operador2.bitfield.sign) && (C == 1))
//    {
//        g, r, st = 0;

//        P = (P >> 1) | (C << (sizeof(P) * 8 - 1));

//        suma.bitfield.expo += 1;

//    }else
//    {
//        int k;
//        if(k = 0)
//        {
//            for (int i = 23; i >= 0; i--) {
//                if ((P >> i) & 1) {
//                    k = 23 - i;
//                    break;
//                }
//            }
//        }else if(k = 1)
//        {
//            r = 0;
//            st = 0;
//            //como se desplaza k bits se añaden k gs a la derecha
//            suma.bitfield.expo = suma.bitfield.expo - k;
//        }
//    }

//    //paso11
//    if(((r == 1) && (st == 1)) || (r ==1) && (st == 0) && (P[0]== 1))
//    {

//    }
//}

int calcular_acarreo(int a, int b) {
    int suma = a + b;
    int bit_acarreo = 1 << 23; // bit de acarreo en la posición más significativa (32 bits en total)
    return (suma & bit_acarreo) > 0 ? 1 : 0; // si el resultado del AND es mayor que cero, hay acarreo
}


