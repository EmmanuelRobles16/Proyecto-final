#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::iniciarNivel(int numero) {
    // Por ahora solo cambia el título de la ventana como prueba
    setWindowTitle(QString("Nivel %1").arg(numero));
}
