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

void ALU::suma()
{

    bitset <24> mantisa1(operador1.numero); // PASARLO A BINARIO

    bitset <24> mantisa2(operador2.numero);

    cout << mantisa1 << endl;
    cout << mantisa2 << endl;

    mantisa1 = convertBinary(mantisa1);
    mantisa2 = convertBinary(mantisa2);

    cout << mantisa1 << endl;
    cout << mantisa2 << endl;

    //paso1  POSIBLE NECESIDAD DE CAMBIAR EL TIPO DE VARIABLES
    bitset<24> P;
    int g = 0, r = 0, st = 0;
    int n = 24; // Numero de bits de la mantisa
    bool intercambio = false;
    bool completado_P = false;

    //paso2
    if(operador1.bitfield.expo < operador2.bitfield.expo)
    {
        swap(operador1, operador2);
        intercambio = true;
    }

    //paso3
    union Code suma;
    suma.bitfield.expo = operador1.bitfield.expo;
    int d = operador1.bitfield.expo - operador2.bitfield.expo;

    if(d<0)
    {
        // ERROR
    }

    //paso4
    if(operador1.bitfield.sign != operador2.bitfield.sign)
    {
        mantisa2 = ~mantisa2.to_ulong() + 1;
    }

    cout << "Complemento a dos: " << endl;
    cout << mantisa2 << endl;

    //paso5
    P = mantisa2;

    //paso6
    // d=0 -> nada d=1->g d=2->g,r d=3 -> g,r y st st->mirar hasta el final si hay un 1
    if (d == 1)
    {
        g = P[d-1];

    } else if(d == 2)
    {
        g = P[d-1];
        r = P[d-2];

    } else if(d == 3)
    {
        g = P[d-1];
        r = P[d-2];

        for (int i = 22; i >= 0; --i) {
            if (P[i]) {
                st = 1;
                break;
            }
        }
    }


    cout << "g" << endl;

    cout << g << endl;

    cout << "r" << endl;

    cout << r << endl;

    cout << "st"<< endl;

    cout << st << endl;


    //paso7
    if(operador1.bitfield.sign != operador2.bitfield.sign)
    {
        P = (P.to_ulong() >> d) | (1 << (P.size() - d));
    }else
    {
        P = (P.to_ulong() >> d) | ((1 << d) - 1) << (sizeof(P) * 8 - d);
    }

    cout << "sign1" << endl;
    cout << operador1.bitfield.sign << endl;
    cout << operador2.bitfield.sign << endl;
    cout << "d" << endl;
    cout << d << endl;
    cout << "P" << endl;
    cout << P << endl;

    //paso8

    P = mantisa1.to_ulong() + P.to_ulong();
    bitset<24> C = calcular_acarreo(mantisa1, P);

    // paso9
    if((operador1.bitfield.sign != operador2.bitfield.sign) && (P[n-1] == 1) && (C == 0))
    {
        P = ~P.to_ulong() + 1;
        completado_P = true;
    }

    // paso10
    if((operador1.bitfield.sign == operador2.bitfield.sign) && (C == 1))
    {
        if(g == 1 || r == 1 || st == 1)
        {
            st = 1;
        }

        r = P[0];

        P = (P.to_ulong() >> 1) | (C.to_ulong() << (sizeof(P) * 8 - 1));

        suma.bitfield.expo += 1;

    }else
    {
        int k = 0;
        for(int i = 23; i >= 0; i--)
        {
            if(P[i] == 1){
                k = 23 - i;
                break;
            }
        }
        //ya teniendo k:

        if(k == 0)
        {
            if(r == 1 || st == 1)
            {
                st = 1;
            }
            r = g;

        }else if(k == 1)
        {
            r = 0;
            st = 0;
            //como se desplaza k bits se añaden k gs a la derecha
            for(int i =0; i < k; i++)
            {
                P =(P.to_ulong() >> 1) | (g << 23);
            }
            suma.bitfield.expo = suma.bitfield.expo - k;
        }
    }

    //paso11
    if(((r == 1) && (st == 1)) || (r ==1) && (st == 0) && (P[0]== 1))
    {
        P = P.to_ulong() + 1;
        bitset<24> uno = 1;
        bitset<24> C2 = calcular_acarreo(P, uno);
        if(C2 == 1)
        {
                P =(P.to_ulong() >> 1) | (C2.to_ulong() << 23);
        }
    }
    bitset<24> mantisaSuma = P;
    //paso12
    if((intercambio ==false) && (completado_P == true))
    {
        suma.bitfield.sign = operador2.bitfield.sign;
    }else
    {
        suma.bitfield.sign = operador1.bitfield.sign;
    }

    // Paso 13
    union Code sumaFinal;
    sumaFinal.bitfield.sign = suma.bitfield.sign;
    sumaFinal.bitfield.expo = suma.bitfield.expo;

    // Se calcula el desplazamiento necesario para normalizar la mantisa de la suma
    int shift = 0;
    for (int i = mantisaSuma.size() - 1; i >= 0; --i) {
        if (mantisaSuma[i] == 1) {
            shift = mantisaSuma.size() - 1 - i;
            break;
        }
    }

    // Se ajusta el exponente de la suma en función del desplazamiento
    sumaFinal.bitfield.expo += shift;

    // Se ajusta la mantisa de la suma según el desplazamiento
    bitset<24> mantisaAjustada = mantisaSuma >> shift;

    // Se guarda la mantisa ajustada en el campo correspondiente de sumaFinal.numero
    sumaFinal.numero = mantisaAjustada.to_ulong();

    // Se muestra el valor de la suma en IEEE 754
    string sumaIEEE = floatToBinaryIEEE754(sumaFinal.numero);
    cout << "Suma en IEEE 754: " << sumaIEEE << endl;
}

bitset<24> ALU::calcular_acarreo(bitset<24> a, bitset<24> b) {
    bitset<24> suma = a.to_ulong() + b.to_ulong();
    bitset<24> bit_acarreo = 1 << 23; // bit de acarreo en la posición más significativa (32 bits en total)
    return (suma.to_ulong() & bit_acarreo.to_ulong()) > 0 ? 1 : 0; // si el resultado del AND es mayor que cero, hay acarreo
}


bitset<24> ALU::convertBinary(bitset<24> mantisa)
{
    // Convertir bitset a entero y luego a cadena binaria
   string s = bitset<24>(mantisa.to_ulong()).to_string();

   // Encontrar la posición del primer bit "1" desde la izquierda
   int i = 0;
   while (s[i] == '0') {
       i++;
   }

   // Desplazar los bits a la derecha esa cantidad de posiciones
   s = s.substr(i) + s.substr(0, i);

   // Convertir la cadena binaria resultante a un nuevo bitset
   bitset<24> result(s);
   return result;
}


// Función auxiliar para convertir un número float a su representación binaria IEEE 754
string ALU::floatToBinaryIEEE754(float value) {
    static_assert(sizeof(float) == sizeof(uint32_t), "Tamaño incorrecto para float y uint32_t");
    uint32_t binary;
    memcpy(&binary, &value, sizeof(float));

    string binaryString;
    for (int i = 24; i >= 0; --i) {
        binaryString += ((binary >> i) & 1) ? '1' : '0';
    }

    return binaryString;
}

