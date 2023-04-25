#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

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

    void convertir_hex();

    void convertir_ieee();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
