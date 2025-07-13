#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "goku.h"
#include <QGraphicsScene>
#include <QPainter>

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
    escena->setBackgroundBrush(Qt::black);  // Fondo de respaldo si algo falla

    if (numero == 1) {
        // Cargar la imagen de fondo de tamaño exacto (800x600)
        QPixmap fondo(":/sprites/fondo_nivel_1.png");
        QGraphicsPixmapItem* fondoItem = escena->addPixmap(fondo);
        fondoItem->setZValue(-1);  // Detrás de Goku
        fondoItem->setPos(0, 0);   // Posicionado exactamente desde la esquina
    }

    // Agregar a Goku en la escena
    goku = new Goku();
    goku->setPos(100, 500);
    escena->addItem(goku);

    // Captura de teclado
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
