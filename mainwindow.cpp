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



void MainWindow::on_botonOperate_clicked() {
    // Crear una instancia de la clase ALU
    ALU alu;
    // Variables para almacenar los resultados en diferentes formatos
    string result754 = "";
    string numA754 = "";
    string numB754 = "";
    QString result = "";
    QString qnumAH;
    QString qnumBH;
    QString qresultadoH;
    float numA = 0;
    float numB = 0;
    QString qnumA754 = "";
    QString qnumB754 = "";
    QString qresult754 = "";
    string numAH;
    string numBH;
    string resultadoH;
    QString num = "";
    QString num2 = "";

    // Comprobar el índice seleccionado en el combobox
    if (ui->comboBox->currentIndex() == 0) {
        // Obtener los números ingresados en los lineEdit y convertirlos a valores float
        num = ui->lineEdit_OP1->text();
        num2 = ui->lineEdit_OP2->text();
        numA = num.toFloat();
        numB = num2.toFloat();

        // Realizar la operación de suma
        float resultado = alu.sumar(numA, numB);

        // Convertir los números y resultados a formato IEEE-754
        numA754 = alu.floattoIEE(numA);
        qnumA754 = QString::fromStdString(numA754);
        ui->text_ieee_op2->setText(qnumA754);

        numB754 = alu.floattoIEE(numB);
        qnumB754 = QString::fromStdString(numB754);
        ui->text_ieee_op1->setText(qnumB754);

        // Convertir los números y resultados a formato hexadecimal
        numAH = ToHex(numA);
        qnumAH = QString::fromStdString(numAH);
        ui->text_hex_op2->setText(qnumAH);

        numBH = ToHex(numB);
        qnumBH = QString::fromStdString(numBH);
        ui->text_hex_op1->setText(qnumBH);

        // Convertir el resultado a formato IEEE-754 y hexadecimal
        result754 = alu.floattoIEE(resultado);
        qresult754 = QString::fromStdString(result754);
        ui->text_ieee_resultado->setText(qresult754);

        resultadoH = ToHex(resultado);
        qresultadoH = QString::fromStdString(resultadoH);
        ui->text_hex_resultado->setText(qresultadoH);

        // Convertir el resultado a formato QString y mostrarlo en el campo de texto
        result = QString::number(resultado);
        ui->text_resultado->setText(result);
    }

    // Repetir la misma lógica para las otras dos opciones del combobox (multiplicación y división)
    if (ui->comboBox->currentIndex() == 1) {
        // Realizar la operación de multiplicación
        num = ui->lineEdit_OP1->text();
        num2 = ui->lineEdit_OP2->text();
        numA = num.toFloat();
        numB = num2.toFloat();
        float resultado=alu.multiplicar(numA, numB);
        numA754 = alu.floattoIEE(numA);
        qnumA754=  QString::fromStdString(numA754);
        ui->text_ieee_op2->setText(qnumA754);
        numB754 = alu.floattoIEE(numB);
        qnumB754=  QString::fromStdString(numB754);
        ui->text_ieee_op1->setText(qnumB754);
        numAH = ToHex(numA);
        qnumAH =  QString::fromStdString(numAH);
        ui->text_hex_op2->setText(qnumAH);
        numBH = ToHex(numB);
        qnumBH=  QString::fromStdString(numBH);
        ui->text_hex_op1->setText(qnumBH);
        result754 = alu.floattoIEE(resultado);
        qresult754= QString::fromStdString(result754);
        ui->text_ieee_resultado->setText(qresult754);
        resultadoH = ToHex(resultado);
        qresultadoH =  QString::fromStdString(resultadoH);
        ui->text_hex_resultado->setText(qresultadoH);
        result = QString::number(resultado);
        ui->text_resultado->setText(result);
    }
    if (ui->comboBox->currentIndex() == 2) {
        // Realizar la operación de división
        num = ui->lineEdit_OP1->text();
        num2 = ui->lineEdit_OP2->text();
        numA = num.toFloat();
        numB = num2.toFloat();
        float resultado=alu.dividir(numA, numB);
        numA754 = alu.floattoIEE(numA);
        qnumA754=  QString::fromStdString(numA754);
        ui->text_ieee_op2->setText(qnumA754);
        numB754 = alu.floattoIEE(numB);
        qnumB754=  QString::fromStdString(numB754);
        ui->text_ieee_op1->setText(qnumB754);
        numAH = ToHex(numA);
        qnumAH =  QString::fromStdString(numAH);
        ui->text_hex_op2->setText(qnumAH);
        numBH = ToHex(numB);
        qnumBH=  QString::fromStdString(numBH);
        ui->text_hex_op1->setText(qnumBH);
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

