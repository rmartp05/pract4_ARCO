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
    std::string ToHex(float value);


private slots:


    void on_botonOperate_clicked();

    void on_botonReset_clicked();

    void on_botonExit_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
