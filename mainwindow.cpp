#include "mainwindow.h"
#include "ui_mainwindow.h"

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




void MainWindow::on_botonSuma_clicked()
{

}


void MainWindow::on_botonMulti_clicked()
{

}


void MainWindow::on_botonDiv_clicked()
{

}


void MainWindow::on_botonIgual_clicked()
{

}


void MainWindow::on_botonReset_clicked()
{

}


void MainWindow::on_botonHistorial_clicked()
{

}

void MainWindow::convertir_hex(){

}

void MainWindow::convertir_ieee(){

}
