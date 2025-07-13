#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "goku.h"
#include <QGraphicsScene>

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
    escena = new QGraphicsScene(0, 0, 800, 600, this);
    ui->graphicsView->setScene(escena);

    goku = new Goku();
    goku->setPos(100, 500);
    escena->addItem(goku);

    this->setFocus();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!goku) {
        QMainWindow::keyPressEvent(event);
        return;
    }

    switch (event->key()) {
    case Qt::Key_Left:
        goku->moverIzquierda();
        break;
    case Qt::Key_Right:
        goku->moverDerecha();
        break;
    case Qt::Key_Space:
        goku->saltar();
        break;
    default:
        QMainWindow::keyPressEvent(event);
        break;
    }
}
