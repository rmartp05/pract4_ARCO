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

/******************************/
//SUMA
/******************************/

float ALU::sumar(float numA, float numB)
{
    union Code a;
    union Code b;
    union Code aux;
    union Code suma;

    a.numero=numA;
    b.numero=numB;

    if(a.numero==0&&b.numero!=0){
        suma.numero=b.numero;
        return suma.numero;
    }else if(b.numero==0&&a.numero!=0){
        suma.numero=a.numero;
        return suma.numero;
    }

    if((a.bitfield.expo-b.bitfield.expo ==0)&&(a.bitfield.partFrac-b.bitfield.partFrac==0)&&(a.bitfield.sign != b.bitfield.sign)){
        suma.numero = 0;
        return suma.numero;
    }

    if(a.bitfield.expo<1){
        a.bitfield.expo=1;
        denormalA=true;
    }

    if (b.bitfield.expo<1){
        b.bitfield.expo=1;
        denormalB=true;
    }

    ma=DtoB(a.bitfield.partFrac,  denormalA);
    mb=DtoB(b.bitfield.partFrac,  denormalB);



    if(a.bitfield.expo<b.bitfield.expo){
        aux = a;
        a = b;
        b = aux;
        ma=DtoB(a.bitfield.partFrac, denormalA);
        mb=DtoB(b.bitfield.partFrac, denormalB);
        operandosIntercambiados = true;
    }
    suma.bitfield.expo = a.bitfield.expo;
    d= a.bitfield.expo - b.bitfield.expo;
    if(d>22){
        d=22;
    }

    if(a.bitfield.sign != b.bitfield.sign){
        mb =complemento(mb);
    }

    P=mb;



    if(d>=1){
        dAux=23-(d-1);
        g=P.at(dAux);
    }

    if(d>=2){
        dAux=23-(d-2);
        r=P.at(dAux);
    }

    if(d>=3){
        if(d==3){
            st=P.at(23);
        }

        for(int i=3; d-i>=0;i++){
            dAux=23-(d-i);
            if(P.at(dAux)==1){
                st=1;
            }
        }

    }



    if(a.bitfield.sign != b.bitfield.sign){
        for(int j=0; j<d; j++){
            for(int i=22; i>0; i--){
                P.at(i)=P.at(i-1);
            }
            P.at(j)=1;
        }
    }else{
        for(int j=0; j<d; j++){
            for(int i=22; i>0; i--){
                P.at(i)=P.at(i-1);
            }
            P.at(j)=0;
        }
    }


    c=sumaBinaria(P, ma);



    if((a.bitfield.sign != b.bitfield.sign)&&(P.at(n-24)==1)&&(c==0)){
        P=complemento(P);
        complementado_P=true;
    }


    if((a.bitfield.sign == b.bitfield.sign && c==1 )){
        if(st==1||g==1||r==1){
            st=1;
        }else{
            st=0;
        }
        r=P.at(23);


        for(int i=23; i>0; i--){
            P.at(i)=P.at(i-1);
        }
        P.at(0)=c;


        suma.bitfield.expo+=1;
    }else{
        int i=0;
        while(i<24 && P.at(i)==0){
            i++;
            k=i;
        }
        if(denormalA==true||denormalB==true){
            k=0;
        }
        if(k==24){
            k=0;
        }
        if(k==0){
            if(st==1||r==1){
                st=1;
            }else{
                st=0;
            }
            r=g;
        }
        if(k>1){
            st=0;
            r=0;
        }

        for(int j=0; j<k; j++){
            for(int i=0; i<23; i++){
                P.at(i)=P.at(i+1);
            }
            P.at(23-j)=g;
        }

        suma.bitfield.expo-=k;
    }


    if((r==1&&st==1)||(r==1&&st==0&&P.at(23)==1)){
        for(int i =0; i<24; i++){
            if(i==23){
                uno.push_back(1);
            }else{
                uno.push_back(0);
            }
        }
        c2=sumaBinaria(P,uno);
        if(c2==1){
            for(int i=n-1; i>0; i--){
                P.at(i)=P.at(i-1);
            }
            P.at(0)=c2;
            suma.bitfield.expo+=1;
        }

    }




    suma.bitfield.partFrac = VectorToInt(P);

    if(operandosIntercambiados==false&&complementado_P==true){
        suma.bitfield.sign=b.bitfield.sign;
    }else{
        suma.bitfield.sign=a.bitfield.sign;
    }
    if(a.bitfield.expo+b.bitfield.expo-127>254){
        if(suma.bitfield.sign==0){
            return INFINITY;
        }
        return -INFINITY;
    }

    return suma.numero;

}

/******************************/
//MULTIPLICACION
/******************************/

float ALU::multiplicar(float numA, float numB){
    union Code a;
    union Code b;
    union Code producto;
    int expo = 0;

    a.numero = numA;
    b.numero = numB;

    if(a.numero==0||b.numero==0){
        if(a.bitfield.expo>254||b.bitfield.expo>254){

            return NAN;
        }

        return 0;
    }

    if(a.bitfield.expo<1){
        a.bitfield.expo=1;
        denormalA=true;
    }

    if (b.bitfield.expo<1){
        b.bitfield.expo=1;
        denormalB=true;
    }

    ma=DtoB(a.bitfield.partFrac,  denormalA);
    mb=DtoB(b.bitfield.partFrac,  denormalB);



    if(a.bitfield.sign==1&&b.bitfield.sign==1){
        producto.bitfield.sign=0;
    }else if (a.bitfield.sign==0&&b.bitfield.sign==0){
        producto.bitfield.sign=0;
    }else{
        producto.bitfield.sign=1;
    }



    if(a.bitfield.expo+b.bitfield.expo-127>254){
        if(producto.bitfield.sign==0){
            return INFINITY;
        }
        return -INFINITY;
    }
    expo = ((a.bitfield.expo+b.bitfield.expo)-127);



    for(int i=0; i<24; i++){
        P.push_back(0);
    }
    for(int i=n-1; i>=0; i--){


        if(ma.at(n-1)==1){
            c=sumaBinaria(P,mb);
        }else{
            c=0;
        }
        for(int i=n-1; i>0; i--){
            ma.at(i)=ma.at(i-1);
        }
        ma.at(0)=P.at(23);
        for(int i=n-1; i>0; i--){
            P.at(i)=P.at(i-1);
        }
        P.at(0)=c;



    }



    if(P.at(0)==0){

        for(int i=0; i<23; i++){
            P.at(i)=P.at(i+1);
        }
        P.at(n-1)=ma.at(0);


    }else{
        expo+=1;
    }



    r=ma.at(n-1);
    for(int i=n-2; i>=0; i--){
        if(ma.at(i)==1){
            st=1;
        }
    }

    for(int i =0; i<24; i++){
        if(i==23){
            uno.push_back(1);
        }else{
            uno.push_back(0);
        }
    }

    if((r==1&&st==1)||(r==1&&st==0&&P.at(0)==1)){
        sumaBinaria(P,uno);
    }


    if(expo>254){
        if(producto.bitfield.sign==0){
            return INFINITY;
        }
        return -INFINITY;
    }
    else if(expo<=0){
        t=1-expo;
        if(t>=n){
            return 0;
        }else{
            for(int i =t; i>0; i--){
                for(int i=n-1; i>0; i--){
                    ma.at(i)=ma.at(i-1);
                }
                ma.at(0)=P.at(23);
                for(int i=n-1; i>0; i--){
                    P.at(i)=P.at(i-1);
                }
                P.at(0)=0;
            }
            expo=1;
        }
    }

    if(denormalA==true||denormalB==true){
        if(expo>1){
            t1=expo-1;
            for(int i=0; i<=n-1; i++){
                if(P.at(i)==0){
                    t2++;
                }else{
                    break;
                }
            }
            if(t2==n){
                for(int i=0; i<=n-1; i++){
                    if(ma.at(i)==0){
                        t2++;
                    }else{
                        break;
                    }
                }
            }

            if(t1>t2){
                t=t2;
            }else{
                t=t1;
            }

            expo=expo-t;

            for(int i =t; i>0; i--){
                for(int i=n-1; i>0; i--){
                    ma.at(i)=ma.at(i-1);
                }
                ma.at(0)=P.at(23);
                for(int i=n-1; i>0; i--){
                    P.at(i)=P.at(i-1);
                }
                P.at(0)=0;
            }


        }
    }
    producto.bitfield.expo=expo;
    producto.bitfield.partFrac=VectorToInt(P);


    return producto.numero;


}

/******************************/
//DIVISION
/******************************/

float ALU::dividir(float numA, float numB){
    union Code a;
    union Code b;
    union Code aux;
    union Code division;

    a.numero=numA;
    b.numero=numB;
    if((b.numero==0)&&(a.numero==0)){
        return NAN;
    }else if(a.numero==0){
        return 0;
    }else if(b.numero==0){
        if(a.bitfield.sign==b.bitfield.sign){
            return INFINITY;
        }else{
            return -INFINITY;
        }
    }

    if(a.bitfield.expo<1){
        a.bitfield.expo=1;
        denormalA=true;
    }

    if (b.bitfield.expo<1){
        b.bitfield.expo=1;
        denormalB=true;
    }

    ma=DtoB(a.bitfield.partFrac,  denormalA);
    mb=DtoB(b.bitfield.partFrac,  denormalB);

    parteEnteraA=ma.at(0);
    parteEnteraB=mb.at(0);


    for(int i=1; i<n; i++){
        parteDecimalA.push_back(ma.at(i));
    }

    for(int i=1; i<n; i++){
        parteDecimalB.push_back(mb.at(i));
    }

    DecimalA=parteEnteraA*pow(10,0);
    for(int i=1; i<23; i++){
        DecimalA=DecimalA+(parteDecimalA.at(i-1)*pow(2,-i));
    }

    DecimalB=parteEnteraB*pow(10,0);

    for(int i=1; i<23; i++){
        DecimalB=DecimalB+(parteDecimalB.at(i-1)*pow(2,-i));


    }

    if(DecimalB>=1&&DecimalB<1.25){
        bPrima=1;
    }else if(DecimalB>=1&&DecimalB<2){
        bPrima=0.80;
    }

    if (a.bitfield.sign==1&&b.bitfield.sign==1){
        division.bitfield.sign=0;
    }else if(a.bitfield.sign==0&&b.bitfield.sign==0){
        division.bitfield.sign=0;
    }else{
        division.bitfield.sign=1;
    }


    X.push_back(DecimalA*bPrima);
    Y.push_back(DecimalB*bPrima);

    int i=0;
    do{
        r1=2-Y.at(i);
        Y.push_back(Y.at(i)*r1);
        X.push_back(X.at(i)*r1);

        i++;
    }while(abs(X.at(i)-X.at(i-1))>pow(10,-4));

    aux.numero=X.at(X.size()-1);
    if(a.bitfield.expo-b.bitfield.expo+aux.bitfield.expo>254){
        if(division.bitfield.sign==0){
            return INFINITY;
        }
        return -INFINITY;
    }
    division.bitfield.expo=a.bitfield.expo-b.bitfield.expo+aux.bitfield.expo;
    division.bitfield.partFrac =aux.bitfield.partFrac;


    return division.numero;

}




int ALU::sumaBinaria(vector<int> a,vector<int> b){
    int cAux=0;

    for(int i=23;i>=0;i--){
        if(a[i]+b[i]+cAux==0){
            a[i]=0;
            cAux=0;

        }
        else if(a[i]+b[i]+cAux==1){
            a[i]=1;
            cAux=0;
        }
        else if(a[i]+b[i]+cAux==2){
            a[i]=0;
            cAux=1;
        }
        else if(a[i]+b[i]+cAux==3){
            a[i]=1;
            cAux=1;

        }
    }
    P=a;

    return cAux;

}


string ALU::floattoIEE (float num){
    union Code a;
    iee="";
    a.numero=num;
    if(a.bitfield.expo>254){
        if(a.bitfield.sign==0){
            return "inf";
        }else{
            return "-inf";
        }
    }
    iee.append("s: "+ to_string(a.bitfield.sign)+ "   " );
    iee.append("e: "+ to_string(a.bitfield.expo)+ "   ");
    iee.append("p: "+ to_string(a.bitfield.partFrac)+ "   ");
    return iee;
}



vector<int> ALU::DtoB(int frac, bool denormal){
    vector<int> vBits;
    copiaNumero=0;
    copiaNumero =frac;

    if(denormal==true){
        vBits.push_back(0);
    }else{
        vBits.push_back(1);
    }

    for (int i = 1; i < contBits ; i++ ){
        vBits.push_back(0);
    }

    copiaNumero =frac;
    ultima = contBits - 1;
    while(copiaNumero != 0){
        vBits[ultima] = copiaNumero % 2;
        copiaNumero = copiaNumero / 2;
        ultima--;
    }
    return vBits;



}

vector<int> ALU :: complemento(vector<int> vBits){
    for (i = 0; i < 24 ; i++ ){
        if(vBits[i] == 0){
            vBits[i] = 1;
        }
        else{
            vBits[i] = 0;
        }
    }
    ultima2=24 - 1;
    while ( (ultima2 >= 0) && (vBits.at(ultima2) == 1)) {
        vBits[ultima2] = 0;
        ultima2--;
    }
    vBits[ultima2] = 1;
    return vBits;
}

unsigned int ALU :: VectorToInt(vector<int> v)
{



    for(int i=n-1 ; i>=0 ; i--){
        numbinario.push_back(v[i]);
    }


    for(int i=0 ; i<n  ; i++){
        result+=numbinario[i]*pow(2,i);
    }
    return result;
}
