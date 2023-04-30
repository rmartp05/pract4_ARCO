#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "alu.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    ALU alu;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_botonSuma_clicked();

    void on_botonMulti_clicked();

    void on_botonDiv_clicked();

    void on_botonIgual_clicked();

    void on_botonReset_clicked();

    void on_botonHistorial_clicked();

    void convertir_hex(QString numero1, QString numero2);

    void convertir_ieee(QString numero1, QString numero2);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
