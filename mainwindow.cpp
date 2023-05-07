#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "alu.h"
#include "sstream"
#include<iostream>
#include<string.h>


#include <stdio.h>

#define STRSIGFOXLENGHT 10

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

string MainWindow:: ToHex(float value) {
    char bf[100];
    sprintf(bf,"0x%08lX", *(unsigned long*) &value);
    string hex(bf);
    return hex;
}










//void MainWindow::on_botonSuma_clicked()
//{

//}


//void MainWindow::on_botonMulti_clicked()
//{
//    QString numero1 = ui->lineEdit_OP1->text();
//    QString numero2 = ui->lineEdit_OP2->text();
//    convertir_hex(numero1,numero2);
//    convertir_ieee(numero1,numero2);
//}


//void MainWindow::on_botonDiv_clicked()
//{
//    QString numero1 = ui->lineEdit_OP1->text();
//    QString numero2 = ui->lineEdit_OP2->text();
//    convertir_hex(numero1,numero2);
//    convertir_ieee(numero1,numero2);
//}


//void MainWindow::on_botonIgual_clicked()//hace la operacion de suma, multi o div y printea los resultados
//{

//}


//void MainWindow::on_botonReset_clicked()
//{

//}


//void MainWindow::on_botonHistorial_clicked()
//{

//}

//void MainWindow::convertir_hex(QString numero1, QString numero2){
//    bool isDecimal_1 = numero1.contains(".");
//    bool isDecimal_2 = numero2.contains(".");
//    unsigned long long int num1;
//    unsigned long long int num2;

//    //hacemos numero1:

//    if (isDecimal_1) {
//        double num_double = numero1.toDouble();
//        unsigned long long int* p = reinterpret_cast<unsigned long long int*>(&num_double);
//        num1 = *p;
//    } else {
//        num1 = numero1.toULongLong();
//    }

//    QString hex_numero1 = QString::number(num1, 16);

//    //hacemos numero2:

//    if (isDecimal_2) {
//        double num_double = numero2.toDouble();
//        unsigned long long int* p = reinterpret_cast<unsigned long long int*>(&num_double);
//        num2 = *p;
//    } else {
//        num2 = numero2.toULongLong();
//    }

//    QString hex_numero2 = QString::number(num2, 16);

//    //"imprimimos" los numeros en hex
//    ui->text_hex_op1->append(hex_numero1);
//    ui->text_hex_op2->append(hex_numero2);
//}

//void MainWindow::convertir_ieee(QString numero1, QString numero2){

//    //"imprimimos" los dos numeros convertidos en ieee
//    ui->text_ieee_op1->append(result1);
//    ui->text_ieee_op2->append(result2);
//}

void MainWindow::on_botonOperate_clicked()
{
    ALU alu;
    string result754="";
    string numA754="";
    string numB754="";
    QString result="";
    QString qnumAH;
    QString qnumBH;
    QString qresultadoH;
    float numA=0;
    float numB=0;
    QString qnumA754 ="";
    QString qnumB754 ="";
    QString qresult754="";
    string numAH;
    string numBH;
    string resultadoH;
    QString num = "";
    QString num2 = "";

    if(ui->comboBox->currentIndex()==0){
        num = ui->lineEdit_OP1->text();
        num2 = ui->lineEdit_OP2->text();
        numA = num.toFloat();
        numB = num2.toFloat();
        float resultado=alu.sumar(numA, numB);
        numA754 = alu.floattoIEE(numA);
        qnumA754=  QString::fromStdString(numA754);
        ui->text_ieee_op2->setText(qnumA754);//creo
        numB754 = alu.floattoIEE(numB);
        qnumB754=  QString::fromStdString(numB754);
        ui->text_ieee_op1->setText(qnumB754);
        numAH = ToHex(numA);
        qnumAH =  QString::fromStdString(numAH);
        ui->text_hex_op2->setText(qnumAH);//H
        numBH = ToHex(numB);
        qnumBH=  QString::fromStdString(numBH);
        ui->text_hex_op1->setText(qnumBH);//H
        result754 = alu.floattoIEE(resultado);
        qresult754= QString::fromStdString(result754);
        ui->text_ieee_resultado->setText(qresult754);
        resultadoH = ToHex(resultado);
        qresultadoH =  QString::fromStdString(resultadoH);
        ui->text_hex_resultado->setText(qresultadoH);
        result = QString::number(resultado);
        ui->text_resultado->setText(result);
    }
    if(ui->comboBox->currentIndex()==1){
        num = ui->lineEdit_OP1->text();
        num2 = ui->lineEdit_OP2->text();
        numA = num.toFloat();
        numB = num2.toFloat();
        float resultado=alu.multiplicar(numA, numB);
        numA754 = alu.floattoIEE(numA);
        qnumA754=  QString::fromStdString(numA754);
        ui->text_ieee_op2->setText(qnumA754);//creo
        numB754 = alu.floattoIEE(numB);
        qnumB754=  QString::fromStdString(numB754);
        ui->text_ieee_op1->setText(qnumB754);
        numAH = ToHex(numA);
        qnumAH =  QString::fromStdString(numAH);
        ui->text_hex_op2->setText(qnumAH);//H
        numBH = ToHex(numB);
        qnumBH=  QString::fromStdString(numBH);
        ui->text_hex_op1->setText(qnumBH);//H
        result754 = alu.floattoIEE(resultado);
        qresult754= QString::fromStdString(result754);
        ui->text_ieee_resultado->setText(qresult754);
        resultadoH = ToHex(resultado);
        qresultadoH =  QString::fromStdString(resultadoH);
        ui->text_hex_resultado->setText(qresultadoH);
        result = QString::number(resultado);
        ui->text_resultado->setText(result);
    }
    if(ui->comboBox->currentIndex()==2){
        num = ui->lineEdit_OP1->text();
        num2 = ui->lineEdit_OP2->text();
        numA = num.toFloat();
        numB = num2.toFloat();
        float resultado=alu.dividir(numA, numB);
        numA754 = alu.floattoIEE(numA);
        qnumA754=  QString::fromStdString(numA754);
        ui->text_ieee_op2->setText(qnumA754);//creo
        numB754 = alu.floattoIEE(numB);
        qnumB754=  QString::fromStdString(numB754);
        ui->text_ieee_op1->setText(qnumB754);
        numAH = ToHex(numA);
        qnumAH =  QString::fromStdString(numAH);
        ui->text_hex_op2->setText(qnumAH);//H
        numBH = ToHex(numB);
        qnumBH=  QString::fromStdString(numBH);
        ui->text_hex_op1->setText(qnumBH);//H
        result754 = alu.floattoIEE(resultado);
        qresult754= QString::fromStdString(result754);
        ui->text_ieee_resultado->setText(qresult754);
        resultadoH = ToHex(resultado);
        qresultadoH =  QString::fromStdString(resultadoH);
        ui->text_hex_resultado->setText(qresultadoH);
        result = QString::number(resultado);
        ui->text_resultado->setText(result);

    }
}


void MainWindow::on_botonReset_clicked()
{
    ui->text_hex_op1->setText("");
    ui->text_hex_op2->setText("");
    ui->text_hex_resultado->setText("");
    ui->text_ieee_resultado->setText("");
    ui->text_ieee_op1->setText("");
    ui->text_ieee_op2->setText("");
    ui->text_resultado->setText("");
    ui->lineEdit_OP1->setText("");
    ui->lineEdit_OP2->setText("");
    ui->comboBox->setCurrentIndex(0);
}


void MainWindow::on_botonExit_clicked()
{
    exit(0);
    delete ui;
}

