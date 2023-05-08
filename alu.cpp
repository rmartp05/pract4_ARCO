#include "alu.h"

ALU::ALU()
{

}

union Code {

    struct{
        unsigned int partFrac : 23;
        unsigned int expo : 8;
        unsigned int sign : 1;
    }bitfield;

    float numero;
    unsigned int numerox;
};

////////////////////////////////
////////////SUMA////////////////
////////////////////////////////


float ALU::sumar(float numA, float numB)
{
    union Code a;
    union Code b;
    union Code aux;
    union Code suma;

    a.numero = numA;  // Asigna el valor de numA a la variable a.numero
    b.numero = numB;  // Asigna el valor de numB a la variable b.numero

    // Comprueba si a.numero es cero y b.numero no es cero,
    // en ese caso asigna el valor de b.numero a suma.numero y lo devuelve
    if (a.numero == 0 && b.numero != 0) {
        suma.numero = b.numero;
        return suma.numero;
    }
    // Comprueba si b.numero es cero y a.numero no es cero,
    // en ese caso asigna el valor de a.numero a suma.numero y lo devuelve
    else if (b.numero == 0 && a.numero != 0) {
        suma.numero = a.numero;
        return suma.numero;
    }

    // Comprueba si los exponentes y las partes fraccionarias son iguales,
    // pero los signos son diferentes. En ese caso, asigna cero a suma.numero y lo devuelve.
    if ((a.bitfield.expo - b.bitfield.expo == 0) && (a.bitfield.partFrac - b.bitfield.partFrac == 0) && (a.bitfield.sign != b.bitfield.sign)) {
        suma.numero = 0;
        return suma.numero;
    }

    // Comprueba si el exponente de a es menor que 1,
    // en ese caso lo establece en 1 y marca denormalA como verdadero
    if (a.bitfield.expo < 1) {
        a.bitfield.expo = 1;
        denormalA = true;
    }

    // Comprueba si el exponente de b es menor que 1,
    // en ese caso lo establece en 1 y marca denormalB como verdadero
    if (b.bitfield.expo < 1) {
        b.bitfield.expo = 1;
        denormalB = true;
    }

    ma = DtoB(a.bitfield.partFrac, denormalA);  // Convierte la parte fraccionaria de a a binario y la guarda en ma
    mb = DtoB(b.bitfield.partFrac, denormalB);  // Convierte la parte fraccionaria de b a binario y la guarda en mb

    // Comprueba si el exponente de a es menor que el exponente de b.
    // En ese caso, intercambia los valores de a y b, así como ma y mb.
    // Luego, actualiza ma y mb con las nuevas partes fraccionarias.
    if (a.bitfield.expo < b.bitfield.expo) {
        aux = a;
        a = b;
        b = aux;
        ma = DtoB(a.bitfield.partFrac, denormalA);
        mb = DtoB(b.bitfield.partFrac, denormalB);
        operandosIntercambiados = true;
    }

    suma.bitfield.expo = a.bitfield.expo;  // Establece el exponente de suma como el exponente de a
    d = a.bitfield.expo - b.bitfield.expo;  // Calcula la diferencia de exponentes y la guarda en d

    if (d > 22) {
        d = 22;  // Si la diferencia de exponentes es mayor a 22, la establece en 22
    }

    // Comprueba si los signos de a y b son diferentes.
    // En ese caso, toma el complemento de mb.
    if (a.bitfield.sign != b.bitfield.sign) {
        mb = complemento(mb);

    }

    // Calcula P como el valor de la parte fraccionaria de b en binario
    P = mb;

    if (d >= 1) {
        dAux = 23 - (d - 1);
        g = P.at(dAux);  // Obtiene el bit de guarda g de P
    }

    if (d >= 2) {
        dAux = 23 - (d - 2);
        r = P.at(dAux);  // Obtiene el bit de redondeo r de P
    }

    if (d >= 3) {
        if (d == 3) {
            st = P.at(23);  // Obtiene el bit sticky st de P si d es igual a 3
        }

        // Comprueba los bits anteriores a d-3 en P para actualizar el bit sticky st
        for (int i = 3; d - i >= 0; i++) {
            dAux = 23 - (d - i);
            if (P.at(dAux) == 1) {
                st = 1;
            }
        }
    }

    if (a.bitfield.sign != b.bitfield.sign) {
        // Realiza el desplazamiento hacia la derecha en P para alinear los bits
        // y ajustar el resultado en caso de suma con signos diferentes
        for (int j = 0; j < d; j++) {
            for (int i = 22; i > 0; i--) {
                P.at(i) = P.at(i - 1);
            }
            P.at(j) = 1;
        }
    } else {
        // Realiza el desplazamiento hacia la derecha en P para alinear los bits
        // y ajustar el resultado en caso de suma con signos iguales
        for (int j = 0; j < d; j++) {
            for (int i = 22; i > 0; i--) {
                P.at(i) = P.at(i - 1);
            }
            P.at(j) = 0;
        }
    }

    c = sumaBinaria(P, ma);  // Realiza la suma binaria entre P y ma, guarda el resultado en c

    if ((a.bitfield.sign != b.bitfield.sign) && (P.at(n - 24) == 1) && (c == 0)) {
        // Si la suma resulta en cero y hay un bit carry en P, complementa P
        // y establece la bandera complementado_P en true
        P = complemento(P);
        complementado_P = true;
    }

    if ((a.bitfield.sign == b.bitfield.sign) && (c == 1)) {
        if (st == 1 || g == 1 || r == 1) {
            st = 1;  // Actualiza el bit sticky st si corresponde
        } else {
            st = 0;
        }
        r = P.at(23);  // Actualiza el bit de redondeo r con el último bit de P

        // Realiza el desplazamiento hacia la derecha en P y agrega el carry c al bit más significativo
        for (int i = 23; i > 0; i--) {
            P.at(i) = P.at(i - 1);
        }
        P.at(0) = c;

        suma.bitfield.expo += 1;  // Incrementa el exponente de la suma en 1
    } else {
        int i = 0;
        while (i < 24 && P.at(i) == 0) {
            i++;
            k = i;
        }
        if (denormalA == true || denormalB == true) {
            k = 0;  // Si los operandos son denormales, k se establece en 0
        }
        if (k == 24) {
            k = 0;  // Si todos los bits de P son cero, k se establece en 0
        }
        if (k == 0) {
            if (st == 1 || r == 1) {
                st = 1;  // Actualiza el bit sticky st si corresponde
            } else {
                st = 0;
            }
            r = g;  // Actualiza el bit de redondeo r con el bit de guarda g
        }
        if (k > 1) {
            st = 0;  // Si k es mayor que 1, se descartan los bits sobrantes y se establece st en 0
            r = 0;
        }

        // Realiza el desplazamiento hacia la izquierda en P para descartar los bits sobrantes
        for (int j = 0; j < k; j++) {
            for (int i = 0; i < 23; i++) {
                P.at(i) = P.at(i + 1);
            }
            P.at(23 - j) = g;
        }

        suma.bitfield.expo -= k;  // Decrementa el exponente de la suma en k
    }

    if ((r == 1 && st == 1) || (r == 1 && st == 0 && P.at(23) == 1)) {
        // Realiza una suma binaria entre P y un vector uno (representando 1 en binario)
        // si se cumple alguna de las condiciones
        for (int i = 0; i < 24; i++) {
            if (i == 23) {
                uno.push_back(1);
            } else {
                uno.push_back(0);
            }
        }
        c2 = sumaBinaria(P, uno); // Realiza la suma binaria entre P y uno

        if (c2 == 1) {
            // Si el resultado de la suma anterior es 1, se realiza un desplazamiento hacia la derecha en P
            // y se incrementa el exponente de la suma en 1
            for (int i = n - 1; i > 0; i--) {
                P.at(i) = P.at(i - 1);
            }
            P.at(0) = c2;
            suma.bitfield.expo += 1;
        }
    }

    // Asigna el valor de la parte fraccionaria de la suma en el campo correspondiente
    suma.bitfield.partFrac = VectorToInt(P);

    if (operandosIntercambiados == false && complementado_P == true) {
        // Si los operandos no fueron intercambiados y P fue complementado, el signo de la suma es el del operando b
        suma.bitfield.sign = b.bitfield.sign;
    } else {
        suma.bitfield.sign = a.bitfield.sign; // De lo contrario, el signo de la suma es el del operando a
    }

    if (a.bitfield.expo + b.bitfield.expo - 127 > 254) {
        // Si el exponente de la suma excede el límite superior permitido, se devuelve +/-INFINITY según el signo
        if (suma.bitfield.sign == 0) {
            return INFINITY;
        }
        return -INFINITY;
    }

    return suma.numero; // Devuelve el valor de la suma en forma de número en coma flotante

}

////////////////////////////////
///////MULTIPLICACION///////////
////////////////////////////////

float ALU::multiplicar(float numA, float numB) {
    union Code a;
    union Code b;
    union Code producto;
    int expo = 0;

    // Asigna los valores de los operandos a y b
    a.numero = numA;
    b.numero = numB;

    if (a.numero == 0 || b.numero == 0) {
        if (a.bitfield.expo > 254 || b.bitfield.expo > 254) {
            // Si alguno de los operandos es NaN, se devuelve NaN
            return NAN;
        }
        // Si alguno de los operandos es cero, el resultado de la multiplicación es cero
        return 0;
    }

    if (a.bitfield.expo < 1) {
        // Si el exponente de a es menor que 1, se ajusta a 1 y se indica que es un número denormalizado
        a.bitfield.expo = 1;
        denormalA = true;
    }

    if (b.bitfield.expo < 1) {
        // Si el exponente de b es menor que 1, se ajusta a 1 y se indica que es un número denormalizado
        b.bitfield.expo = 1;
        denormalB = true;
    }

    // Convierte la parte fraccionaria de a y b en forma binaria
    ma = DtoB(a.bitfield.partFrac, denormalA);
    mb = DtoB(b.bitfield.partFrac, denormalB);

    if (a.bitfield.sign == 1 && b.bitfield.sign == 1) {
        // Si ambos operandos tienen el mismo signo negativo, el signo del producto es positivo
        producto.bitfield.sign = 0;
    } else if (a.bitfield.sign == 0 && b.bitfield.sign == 0) {
        // Si ambos operandos tienen el mismo signo positivo, el signo del producto es positivo
        producto.bitfield.sign = 0;
    } else {
        // Si los operandos tienen signos diferentes, el signo del producto es negativo
        producto.bitfield.sign = 1;
    }

    if (a.bitfield.expo + b.bitfield.expo - 127 > 254) {
        // Si el exponente del producto excede el límite superior permitido, se devuelve +/-INFINITY según el signo
        if (producto.bitfield.sign == 0) {
            return INFINITY;
        }
        return -INFINITY;
    }

    expo = (a.bitfield.expo + b.bitfield.expo) - 127;

    // Inicializa el vector P con ceros
    for (int i = 0; i < 24; i++) {
        P.push_back(0);
    }

    for (int i = n - 1; i >= 0; i--) {
        if (ma.at(n - 1) == 1) {
            // Si el bit más significativo de ma es 1, se realiza una suma binaria entre P y mb
            c = sumaBinaria(P, mb);
        } else {
            c = 0;
        }

        // Realiza un desplazamiento hacia la derecha en ma
        for (int i = n - 1; i > 0; i--) {
            ma.at(i) = ma.at(i - 1);
        }
        ma.at(0) = P.at(23);

        // Realiza un desplazamiento hacia la derecha en P
        for (int i = n - 1; i > 0; i--) {
            P.at(i) = P.at(i - 1);
        }
        P.at(0) = c;
    }

    if (P.at(0) == 0) {
        // Si el bit más significativo de P es cero, se realiza un desplazamiento hacia la izquierda en P
        for (int i = 0; i < 23; i++) {
            P.at(i) = P.at(i + 1);
        }
        P.at(n - 1) = ma.at(0);
    } else {
        expo += 1;
    }

    r = ma.at(n - 1);

    // Verifica si hay algún bit distinto de cero en ma
    for (int i = n - 2; i >= 0; i--) {
        if (ma.at(i) == 1) {
            st = 1;
        }
    }

    // Crea un vector "uno" con un uno en la posición más significativa y ceros en las demás posiciones
    for (int i = 0; i < 24; i++) {
        if (i == 23) {
            uno.push_back(1);
        } else {
            uno.push_back(0);
        }
    }

    if ((r == 1 && st == 1) || (r == 1 && st == 0 && P.at(0) == 1)) {
        // Si se cumple alguna de las condiciones, se realiza una suma binaria entre P y uno
        sumaBinaria(P, uno);
    }

    if (expo > 254) {
        // Si el exponente del producto excede el límite superior permitido, se devuelve +/-INFINITY según el signo
        if (producto.bitfield.sign == 0) {
            return INFINITY;
        }
        return -INFINITY;
    } else if (expo <= 0) {
        // Si el exponente del producto es menor o igual a cero
        t = 1 - expo;
        if (t >= n) {
            return 0;
        } else {
            // Realiza desplazamientos hacia la izquierda en ma y P
            for (int i = t; i > 0; i--) {
                for (int i = n - 1; i > 0; i--) {
                    ma.at(i) = ma.at(i - 1);
                }
                ma.at(0) = P.at(23);
                for (int i = n - 1; i > 0; i--) {
                    P.at(i) = P.at(i - 1);
                }
                P.at(0) = 0;
            }
            expo = 1;
        }
    }
    if (denormalA == true || denormalB == true) {
        if (expo > 1) {
            t1 = expo - 1;

            // Calcula la cantidad de ceros consecutivos al comienzo de P
            for (int i = 0; i <= n - 1; i++) {
                if (P.at(i) == 0) {
                    t2++;
                } else {
                    break;
                }
            }

            // Si todos los bits de P son ceros, busca la cantidad de ceros consecutivos en ma
            if (t2 == n) {
                for (int i = 0; i <= n - 1; i++) {
                    if (ma.at(i) == 0) {
                        t2++;
                    } else {
                        break;
                    }
                }
            }

            t = (t1 > t2) ? t2 : t1; // Calcula el valor mínimo entre t1 y t2

            expo = expo - t; // Ajusta el exponente restando el valor mínimo encontrado

            // Realiza desplazamientos hacia la izquierda en ma y P
            for (int i = t; i > 0; i--) {
                for (int i = n - 1; i > 0; i--) {
                    ma.at(i) = ma.at(i - 1);
                }
                ma.at(0) = P.at(23);
                for (int i = n - 1; i > 0; i--) {
                    P.at(i) = P.at(i - 1);
                }
                P.at(0) = 0;
            }
        }
    }

    producto.bitfield.expo = expo; // Asigna el exponente al producto
    producto.bitfield.partFrac = VectorToInt(P); // Convierte el vector P en la parte fraccionaria del producto

    return producto.numero; // Devuelve el resultado de la multiplicación
}


////////////////////////////////
///////////DIVISION/////////////
////////////////////////////////

float ALU::dividir(float numA, float numB) {
    union Code a;
    union Code b;
    union Code aux;
    union Code division;

    a.numero = numA;
    b.numero = numB;

    // Verificar casos especiales de división por cero
    if ((b.numero == 0) && (a.numero == 0)) {
        return NAN; // NaN: Indeterminación
    } else if (a.numero == 0) {
        return 0; // División de cero entre un número distinto de cero es cero
    } else if (b.numero == 0) {
        if (a.bitfield.sign == b.bitfield.sign) {
            return INFINITY; // Infinito positivo
        } else {
            return -INFINITY; // Infinito negativo
        }
    }

    // Verificar si los números son denormalizados y ajustar los exponentes
    if (a.bitfield.expo < 1) {
        a.bitfield.expo = 1;
        denormalA = true;
    }

    if (b.bitfield.expo < 1) {
        b.bitfield.expo = 1;
        denormalB = true;
    }

    ma = DtoB(a.bitfield.partFrac, denormalA); // Convertir la parte fraccionaria de a a binario
    mb = DtoB(b.bitfield.partFrac, denormalB); // Convertir la parte fraccionaria de b a binario

    parteEnteraA = ma.at(0); // Obtener la parte entera de a
    parteEnteraB = mb.at(0); // Obtener la parte entera de b

    // Obtener la parte decimal de a
    for (int i = 1; i < n; i++) {
        parteDecimalA.push_back(ma.at(i));
    }

    // Obtener la parte decimal de b
    for (int i = 1; i < n; i++) {
        parteDecimalB.push_back(mb.at(i));
    }

    DecimalA = parteEnteraA * pow(10, 0);
    for (int i = 1; i < 23; i++) {
        DecimalA = DecimalA + (parteDecimalA.at(i - 1) * pow(2, -i));
    }

    DecimalB = parteEnteraB * pow(10, 0);

    for (int i = 1; i < 23; i++) {
        DecimalB = DecimalB + (parteDecimalB.at(i - 1) * pow(2, -i));
    }

    // Calcular bPrima dependiendo del rango de DecimalB
    if (DecimalB >= 1 && DecimalB < 1.25) {
        bPrima = 1;
    } else if (DecimalB >= 1 && DecimalB < 2) {
        bPrima = 0.80;
    }

    // Determinar el signo del resultado de la división
    if (a.bitfield.sign == 1 && b.bitfield.sign == 1) {
        division.bitfield.sign = 0;
    } else if (a.bitfield.sign == 0 && b.bitfield.sign == 0) {
        division.bitfield.sign = 0;
    } else {
        division.bitfield.sign = 1;
    }

    X.push_back(DecimalA * bPrima);
    Y.push_back(DecimalB * bPrima);

    int i = 0;
    do {
        r1 = 2 - Y.at(i);
        Y.push_back(Y.at(i) * r1);
        X.push_back(X.at(i) * r1);

        i++;
    } while (abs(X.at(i) - X.at(i - 1)) > pow(10, -4));

    aux.numero = X.at(X.size() - 1);

    // Verificar si el exponente resultante está fuera del rango permitido
    if (a.bitfield.expo - b.bitfield.expo + aux.bitfield.expo > 254) {
        if (division.bitfield.sign == 0) {
            return INFINITY;
        }
        return -INFINITY;
    }

    division.bitfield.expo = a.bitfield.expo - b.bitfield.expo + aux.bitfield.expo;
    division.bitfield.partFrac = aux.bitfield.partFrac;

    return division.numero;
}


int ALU::sumaBinaria(vector<int> a, vector<int> b) {
    int cAux = 0;

    for (int i = 23; i >= 0; i--) {
        // Realizar la suma binaria de los bits y el acarreo auxiliar
        if (a[i] + b[i] + cAux == 0) {
            a[i] = 0;
            cAux = 0;
        } else if (a[i] + b[i] + cAux == 1) {
            a[i] = 1;
            cAux = 0;
        } else if (a[i] + b[i] + cAux == 2) {
            a[i] = 0;
            cAux = 1;
        } else if (a[i] + b[i] + cAux == 3) {
            a[i] = 1;
            cAux = 1;
        }
    }
    P = a;

    return cAux;
}

string ALU::floattoIEE(float num) {
    union Code a;
    iee = "";
    a.numero = num;
    if (a.bitfield.expo > 254) {
        if (a.bitfield.sign == 0) {
            return "inf";
        } else {
            return "-inf";
        }
    }
    // Construir la representación de punto flotante IEEE 754
    iee.append("s: " + to_string(a.bitfield.sign) + "   ");
    iee.append("e: " + to_string(a.bitfield.expo) + "   ");
    iee.append("p: " + to_string(a.bitfield.partFrac) + "   ");
    return iee;
}

vector<int> ALU::DtoB(int frac, bool denormal) {
    vector<int> vBits;
    copiaNumero = 0;
    copiaNumero = frac;

    if (denormal == true) {
        vBits.push_back(0);
    } else {
        vBits.push_back(1);
    }

    // Rellenar con ceros el resto de los bits
    for (int i = 1; i < contBits; i++) {
        vBits.push_back(0);
    }

    copiaNumero = frac;
    ultima = contBits - 1;
    // Convertir el número decimal en binario
    while (copiaNumero != 0) {
        vBits[ultima] = copiaNumero % 2;
        copiaNumero = copiaNumero / 2;
        ultima--;
    }
    return vBits;
}

vector<int> ALU::complemento(vector<int> vBits) {
    // Complemento a uno del número binario
    for (i = 0; i < 24; i++) {
        if (vBits[i] == 0) {
            vBits[i] = 1;
        } else {
            vBits[i] = 0;
        }
    }

    ultima2 = 24 - 1;
    // Encontrar el último bit a partir del cual se realiza el complemento a uno
    while ((ultima2 >= 0) && (vBits.at(ultima2) == 1)) {
        vBits[ultima2] = 0;
        ultima2--;
    }
    vBits[ultima2] = 1;
    return vBits;
}

unsigned int ALU::VectorToInt(vector<int> v) {
    // Convertir el vector binario a un número entero
    for (int i = n - 1; i >= 0; i--) {
        numbinario.push_back(v[i]);
    }

    for (int i = 0; i < n; i++) {
        result += numbinario[i] * pow(2, i);
    }
    return result;
}
