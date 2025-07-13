#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "goku.h"
#include "enemigovolador.h"
#include "hud.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
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
    // Escena más ancha que la vista para permitir scroll horizontal
    escena = new QGraphicsScene(0, 0, 1600, 600, this);
    ui->graphicsView->setScene(escena);

    escena->setBackgroundBrush(Qt::black); // color de respaldo

    // Fondo que se repite horizontalmente a lo largo de la escena
    if (numero == 1) {
        QPixmap fondoBase(":/sprites/fondo_nivel_1.png");
        QPixmap fondoTile(escena->width(), escena->height());
        fondoTile.fill(Qt::transparent);
        QPainter p(&fondoTile);
        p.drawTiledPixmap(QRectF(0, 0, escena->width(), escena->height()), fondoBase);
        p.end();
        QGraphicsPixmapItem *fondoItem = escena->addPixmap(fondoTile);
        fondoItem->setZValue(-1); // detrás de todo
        fondoItem->setPos(0, 0);
    }
    // Agregar a Goku en la escena
    goku = new Goku();
    goku->setPos(100, 500);
    escena->addItem(goku);
    actualizarCamara();

    // Crear HUD de vida
    hud = new HUD();
    hud->setZValue(10); // por encima de otros elementos
    hud->setPos(10, 30);
    escena->addItem(hud);
    connect(goku, &Goku::vidaActualizada, hud, &HUD::actualizar);
    hud->actualizar(goku->getVida());

    // Timer principal del juego (física y cámara)
    if (!timer) {
            timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MainWindow::actualizarJuego);
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


void MainWindow::actualizarJuego()
{
    if (!goku) return;
    goku->actualizarFisica();
    actualizarCamara();
}

void MainWindow::actualizarCamara()
{
    if (!goku || !escena) return;

    QGraphicsView *view = ui->graphicsView;
    const qreal viewWidth = view->viewport()->width();
    const qreal halfView = viewWidth / 2.0;
    const qreal sceneWidth = escena->width();

    // Limitar posición de Goku dentro del mapa
    qreal limiteIzquierdo = 0.0;
    qreal limiteDerecho = sceneWidth - goku->boundingRect().width();
    limitarX(goku, limiteIzquierdo, limiteDerecho);
    qreal nuevaX = goku->x();

    // Calcular centro deseado para la vista
    qreal centroX = nuevaX;
    qreal margenIzquierdo = halfView;
    qreal margenDerecho = sceneWidth - halfView;

    if (centroX < margenIzquierdo)
        centroX = margenIzquierdo;
    else if (centroX > margenDerecho)
        centroX = margenDerecho;
    // Centrar la vista solo horizontalmente
    view->centerOn(centroX, escena->height() / 2.0);
        // Mantener el HUD fijo en la vista
    if (hud) {
        hud->setPos(view->mapToScene(QPoint(10, 30)));
    }
}

void MainWindow::limitarX(QGraphicsItem *item, qreal minX, qreal maxX)
{
    if (!item) return;
    qreal x = item->x();
    if (x < minX)
        x = minX;
    else if (x > maxX)
        x = maxX;
    item->setX(x);
}
