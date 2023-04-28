#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "sstream"
#include "bitset"
#include "cmath"

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
        num2 = numero2.toULongLong();
    }

    QString hex_numero2 = QString::number(num2, 16);

    //"imprimimos" los numeros en hex
    ui->text_hex_op1->append(hex_numero1);
    ui->text_hex_op2->append(hex_numero2);
}

void MainWindow::convertir_ieee(QString numero1, QString numero2){
    bool isDecimal_1 = numero1.contains(".");
    bool isDecimal_2 = numero2.contains(".");

    double num;
    //hacemos numero1
    if(isDecimal_1){
        num = stod(numero1.toStdString());
    }else{
        num = stoi(numero1.toStdString());
    }

    bitset<64> bits(reinterpret_cast<unsigned long long>(&num));

    int sign = bits[63];
    unsigned long long num_bits = bits.to_ullong();
    int exponent = static_cast<int>((num_bits & 0x7FF0000000000000ULL) >> 52) - 1023;
    double fraction = 1.0;
    for (int i = 51; i >= 0; i--) {
        if (bits[i] == 1) {
            fraction += pow(2.0, i - 52);
        }
    }

    QString result1;
    if (sign == 1) {
        result1 += "-";
    }
    result1 += "1.";
    for (int i = 51; i >= 0; i--) {
        if (i == 51 && bits[i] == 0) {
            continue;
        }
        result1 += QString::number(bits[i]);
    }
    result1 += " x 2^" + QString::number(exponent);

    //hacemos numero2
    double num2;
    if(isDecimal_2){
        num2 = stod(numero2.toStdString());
    }else{
        num2 = stoi(numero2.toStdString());
    }

    bitset<64> bits2(reinterpret_cast<unsigned long long>(&num2));

    int sign2 = bits2[63];
    unsigned long long num_bits2 = bits2.to_ullong();
    int exponent2 = static_cast<int>((num_bits2 & 0x7FF0000000000000ULL) >> 52) - 1023;
    double fraction2 = 1.0;

    for (int i = 51; i >= 0; i--) {
        if (bits2[i] == 1) {
            fraction2 += pow(2.0, i - 52);
        }
    }

    QString result2;
    if (sign2 == 1) {
        result2 += "-";
    }
    result2 += "1.";
    for (int i = 51; i >= 0; i--) {
        if (i == 51 && bits2[i] == 0) {
            continue;
        }
        result2 += QString::number(bits2[i]);
    }
    result2 += " x 2^" + QString::number(exponent2);

    //"imprimimos" los dos numeros convertidos en ieee
    ui->text_ieee_op1->append(result1);
    ui->text_ieee_op2->append(result2);
}
