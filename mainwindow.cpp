#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "sstream"
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



//guardar los numeros en el historial
//los metodos suma multi y div solo llaman a hex y ieee y los printean en op1 y op2 los dos
void MainWindow::on_botonSuma_clicked()
{
    QString numero1 = ui->lineEdit_OP1->text();
    QString numero2 = ui->lineEdit_OP2->text();
    convertir_hex(numero1,numero2);
    convertir_ieee(numero1,numero2);
}


void MainWindow::on_botonMulti_clicked()
{
    QString numero1 = ui->lineEdit_OP1->text();
    QString numero2 = ui->lineEdit_OP2->text();
    convertir_hex(numero1,numero2);
    convertir_ieee(numero1,numero2);
}


void MainWindow::on_botonDiv_clicked()
{
    QString numero1 = ui->lineEdit_OP1->text();
    QString numero2 = ui->lineEdit_OP2->text();
    convertir_hex(numero1,numero2);
    convertir_ieee(numero1,numero2);
}


void MainWindow::on_botonIgual_clicked()//hace la operacion de suma, multi o div y printea los resultados
{

}


void MainWindow::on_botonReset_clicked()
{

}


void MainWindow::on_botonHistorial_clicked()
{

}

void MainWindow::convertir_hex(QString numero1, QString numero2){
    bool isDecimal_1 = numero1.contains(".");
    bool isDecimal_2 = numero2.contains(".");
    unsigned long long int num1;
    unsigned long long int num2;

    //hacemos numero1:

    if (isDecimal_1) {
        double num_double = numero1.toDouble();
        unsigned long long int* p = reinterpret_cast<unsigned long long int*>(&num_double);
        num1 = *p;
    } else {
        num1 = numero1.toULongLong();
    }

    QString hex_numero1 = QString::number(num1, 16);

    //hacemos numero2:

    if (isDecimal_2) {
        double num_double = numero2.toDouble();
        unsigned long long int* p = reinterpret_cast<unsigned long long int*>(&num_double);
        num2 = *p;
    } else {
        num2 = numero1.toULongLong();
    }

    QString hex_numero2 = QString::number(num2, 16);

    //"imprimimos" los numeros en hex
    ui->text_hex_op1->append(hex_numero1);
    ui->text_hex_op2->append(hex_numero2);
}

void MainWindow::convertir_ieee(QString numero1, QString numero2){

}
