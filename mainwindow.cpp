#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "goku.h"
#include "enemigovolador.h"
#include "hud.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    if (timer) {
        timer->stop();
    }
    if (timerEnemigos) {
        timerEnemigos->stop();
    }
    if (timerGeneradorEnemigos) {
        timerGeneradorEnemigos->stop();
    }
    if (timerColisiones) {
        timerColisiones->stop();
    }
    for (EnemigoVolador* e : enemigos) {
        escena->removeItem(e);
        delete e;
    }
    enemigos.clear();
    delete hud;
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

    // Crear HUD de vida
    hud = new HUD();
    hud->setPos(10, 10);
    escena->addItem(hud);
    connect(goku, &Goku::vidaActualizada, hud, &HUD::actualizar);
    hud->actualizar(goku->getVida());

    // Timer para la física
    if (!timer) {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, goku, &Goku::actualizarFisica);
    }
    timer->start(30);

    // Timer para movimiento de enemigos
    if (!timerEnemigos) {
        timerEnemigos = new QTimer(this);
        connect(timerEnemigos, &QTimer::timeout, this, &MainWindow::actualizarEnemigos);
    }
    timerEnemigos->start(30);

    // Timer para creacion de enemigos
    if (!timerGeneradorEnemigos) {
        timerGeneradorEnemigos = new QTimer(this);
        connect(timerGeneradorEnemigos, &QTimer::timeout, this, &MainWindow::crearEnemigo);
    }
    timerGeneradorEnemigos->start(QRandomGenerator::global()->bounded(2000, 4001));

    // Timer para verificar colisiones
    if (!timerColisiones) {
        timerColisiones = new QTimer(this);
        connect(timerColisiones, &QTimer::timeout, this, &MainWindow::verificarColisiones);
    }
    timerColisiones->start(30);

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
        goku->activarPlaneo();
        break;
    default:
        QMainWindow::keyPressEvent(event);
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (!goku) {
        QMainWindow::keyReleaseEvent(event);
        return;
    }

    if (event->key() == Qt::Key_Space) {
        goku->desactivarPlaneo();
    } else {
        QMainWindow::keyReleaseEvent(event);
    }
}
void MainWindow::actualizarEnemigos()
{
    for (int i = 0; i < enemigos.size(); ) {
        EnemigoVolador *e = enemigos[i];
        e->actualizarMovimiento();
        if (e->estaFueraDePantalla()) {
            escena->removeItem(e);
            delete e;
            enemigos.remove(i);
        } else {
            ++i;
        }
    }
}

void MainWindow::crearEnemigo()
{
    EnemigoVolador *enemigo = new EnemigoVolador();
    float yPos = QRandomGenerator::global()->bounded(100, 500);
    enemigo->setPos(800, yPos);
    enemigo->establecerYInicial(yPos);
    escena->addItem(enemigo);
    enemigos.append(enemigo);
    timerGeneradorEnemigos->start(QRandomGenerator::global()->bounded(2000, 4001));
}




void MainWindow::verificarColisiones()
{
    if (!goku) return;
    QList<QGraphicsItem*> colisiones = goku->collidingItems();
    for (QGraphicsItem* item : colisiones) {
        EnemigoVolador* enemigo = dynamic_cast<EnemigoVolador*>(item);
        if (enemigo) {
            goku->recibirDanio(20);
            escena->removeItem(enemigo);
            enemigos.removeOne(enemigo);
            delete enemigo;
            if (goku->getVida() <= 0) {
                QMessageBox::information(this, "Fin del juego", "Goku ha sido derrotado");
                close();
                return;
            }
        }
    }
}
