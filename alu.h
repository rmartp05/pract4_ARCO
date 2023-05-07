#ifndef ALU_H
#define ALU_H
#include <vector>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "string.h"
#include <sstream>
using namespace std;

class ALU
{
public:
public:
    ALU();
    float sumar(float numA, float numB);
    float multiplicar(float numA, float numB);
    float dividir(float numA, float numB);
    int sumaBinaria(vector<int> P,vector<int> ma);
    string floattoIEE (float num);
    vector<int> DtoB(int partFrac, bool denormal);
    vector<int> complemento(vector<int> vBits);
    unsigned int VectorToInt(vector<int> v);

private:
    int g=0;
    int r=0;
    int st=0;
    int n=24;
    int c=0;
    int c2=0;
    int d=0;
    int k=0;
    int t=0;
    int t1=0;
    int t2=0;
    int dAux;
    int copiaNumero=0;
    int contBits=24;
    int ultima=0;
    int i;
    int ultima2;
    int parteEnteraA=0;
    int parteEnteraB=0;
    float DecimalA=0;
    float DecimalB=0;
    float bPrima=0;
    float r1=0;
    unsigned int result=0;
    vector<int> mb;
    vector<int> ma;
    vector<int> P;
    vector<int> uno;
    vector<int> parteDecimalB;
    vector<int> parteDecimalA;
    vector<int> numbinario;
    vector<float> Y;
    vector<float> X;
    string iee;
    bool operandosIntercambiados = false;
    bool complementado_P = false;
    bool denormalA = false;
    bool denormalB = false;
};

#endif // ALU_H
