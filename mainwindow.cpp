#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "goku.h"
#include "enemigovolador.h"
#include "dialogoretro.h"
#include "hud.h"
#include "plataforma.h"
#include "proyectil.h"
#include "metafinal.h"
#include "esferadragon.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>

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
    if (timerAtaqueTenshinhan) {
        timerAtaqueTenshinhan->stop();
    }
    for (EnemigoVolador* e : enemigos) {
        escena->removeItem(e);
        delete e;
    }
    enemigos.clear();
    for (Plataforma* p : Plataformas) {
        escena->removeItem(p);
        delete p;
    }
    Plataformas.clear();
    if (esfera) {
        escena->removeItem(esfera);
        delete esfera;
        esfera = nullptr;
    }
    if (metaFinal) {
        escena->removeItem(metaFinal);
        delete metaFinal;
        metaFinal = nullptr;
    }
    if (tenshinhan) {
        escena->removeItem(tenshinhan);
        delete tenshinhan;
        tenshinhan = nullptr;
    }
    if (hudTenshinhan) {
        escena->removeItem(hudTenshinhan);
        delete hudTenshinhan;
        hudTenshinhan = nullptr;
    }
    if (musicaFondo) {
        musicaFondo->stop();
        delete musicaFondo;
        musicaFondo = nullptr;
        delete audioOutput;
        audioOutput = nullptr;
    }
    for (Proyectil* p : proyectiles) {
        escena->removeItem(p);
        delete p;
    }
    proyectiles.clear();
    proyectilGoku = nullptr;
    delete hud;
    delete ui;
}
void MainWindow::iniciarNivel(int numero) {
    nivelActual = numero;
    carriles = {530, 500, 450, 400};
    indiceCarril = 0;
    int anchoEscena = (numero == 1) ? 2400 : 800;
    escena = new QGraphicsScene(0, 0, anchoEscena, 600, this);
    ui->graphicsView->setScene(escena);

    if (!musicaFondo) {
        musicaFondo = new QMediaPlayer(this);
        audioOutput = new QAudioOutput(this);
        musicaFondo->setAudioOutput(audioOutput);
        musicaFondo->setSource(QUrl("qrc:/audio/musica_nivel1.wav"));
        musicaFondo->setLoops(QMediaPlayer::Infinite);
        musicaFondo->play();
    }
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
        fondoItem->setZValue(-1);
        fondoItem->setPos(0, 0);
    } else if (numero == 2) {
        QPixmap fondoBase(":/sprites/fondo_nivel_2.png");
        QGraphicsPixmapItem *fondoItem = escena->addPixmap(fondoBase.scaled(escena->width(), escena->height()));
        fondoItem->setZValue(-1);
        fondoItem->setPos(0, 0);
        const int altoCarril = 100;
        for (int y : carriles) {
            escena->addRect(0, y - altoCarril / 2, escena->width(), altoCarril, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
        }
    }
    // Agregar a Goku en la escena
    goku = new Goku();
    goku->setPos(100, carriles[indiceCarril]);
    escena->addItem(goku);
    connect(goku, &Goku::ataqueLanzado, this, [this]() {
        if (proyectilGoku)
            return;
        proyectilGoku = new Proyectil(Proyectil::DeGoku);
        proyectilGoku->setPos(goku->x() + goku->boundingRect().width(), goku->y() + goku->boundingRect().height()/2);
        escena->addItem(proyectilGoku);
        proyectiles.append(proyectilGoku);
        connect(proyectilGoku, &Proyectil::eliminado, this, [this](Proyectil* p){
            proyectiles.removeOne(p);
            if (proyectilGoku == p)
                proyectilGoku = nullptr;
        });
    });
    actualizarCamara();

    if (numero == 1) {
        // Crear plataformas iniciales
        Plataforma *p1 = new Plataforma(300, 500, 100, 20);
        escena->addItem(p1);
        Plataformas.append(p1);
        Plataforma *p2 = new Plataforma(600, 320, 120, 20);
        escena->addItem(p2);
        Plataformas.append(p2);

        // Agregar plataformas adicionales
        Plataforma *p3 = new Plataforma(900, 200, 100, 20);
        escena->addItem(p3);
        Plataformas.append(p3);

        Plataforma *p4 = new Plataforma(1100, 400, 100, 20);
        escena->addItem(p4);
        Plataformas.append(p4);

        Plataforma *p5 = new Plataforma(1300, 200, 100, 20);
        escena->addItem(p5);
        Plataformas.append(p5);

        // Nuevas plataformas para el tramo extendido
        Plataforma *p6 = new Plataforma(1500, 450, 100, 20);
        escena->addItem(p6);
        Plataformas.append(p6);

        Plataforma *p7 = new Plataforma(1700, 350, 120, 20);
        escena->addItem(p7);
        Plataformas.append(p7);

        Plataforma *p8 = new Plataforma(1900, 250, 100, 20);
        escena->addItem(p8);
        Plataformas.append(p8);

        Plataforma *p9 = new Plataforma(2100, 180, 100, 20);
        escena->addItem(p9);
        Plataformas.append(p9);

        // Esfera del Dragon
        esfera = new EsferaDragon();
        esfera->setPos(1800, 300);
        escena->addItem(esfera);

        // Meta del nivel
        metaFinal = new MetaFinal();
        metaFinal->setPos(2350, 150);
        escena->addItem(metaFinal);

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
    } else if (numero == 2) {
        tenshinhan = new Tenshinhan();
        escena->addItem(tenshinhan);
        tenshinhan->setZValue(1);

        // HUD de Tenshinhan
        hudTenshinhan = new HUD(80, Qt::red);
        hudTenshinhan->setZValue(10);
        escena->addItem(hudTenshinhan);
        connect(tenshinhan, &Tenshinhan::vidaActualizada, hudTenshinhan, &HUD::actualizar);
        hudTenshinhan->actualizar(tenshinhan->getVida());
        int xHud = ui->graphicsView->viewport()->width() - hudTenshinhan->rect().width() - 10;
        hudTenshinhan->setPos(ui->graphicsView->mapToScene(QPoint(xHud, 30)));

        if (!timerAtaqueTenshinhan) {
            timerAtaqueTenshinhan = new QTimer(this);
            connect(timerAtaqueTenshinhan, &QTimer::timeout, this, &MainWindow::lanzarProyectiles);
        }
        timerAtaqueTenshinhan->start(2000);

        if (!timerColisiones) {
            timerColisiones = new QTimer(this);
            connect(timerColisiones, &QTimer::timeout, this, &MainWindow::verificarColisiones);
        }
        timerColisiones->start(30);
    }


    // Crear HUD de vida
    hud = new HUD();
    hud->setZValue(10);
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

    this->setFocus();
}



void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!goku) {
        QMainWindow::keyPressEvent(event);
        return;
    }

    if (nivelActual == 2) {
        switch (event->key()) {
        case Qt::Key_W:
            if (indiceCarril < carriles.size() - 1) {
                indiceCarril++;
                goku->setPos(100, carriles[indiceCarril]);
            }
            break;
        case Qt::Key_S:
            if (indiceCarril > 0) {
                indiceCarril--;
                goku->setPos(100, carriles[indiceCarril]);
            }
            break;
        default:
            QMainWindow::keyPressEvent(event);
            break;
        }
    } else {
        switch (event->key()) {
        case Qt::Key_Left:
            goku->moverIzquierda();
            break;
        case Qt::Key_Right:
            goku->moverDerecha();
            break;
        case Qt::Key_Space:
            goku->atacar();
            break;
        default:
            QMainWindow::keyPressEvent(event);
            break;
        }
    }
}


void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (!goku) {
        QMainWindow::keyReleaseEvent(event);
        return;
    }

    if (nivelActual == 1) {
        switch (event->key()) {
        case Qt::Key_Left:
        case Qt::Key_Right:
            goku->detenerAnimacionCaminar();
            break;
        default:
            QMainWindow::keyReleaseEvent(event);
            break;
        }
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
    // Generar de 2 a 4 enemigos
    int cantidad = QRandomGenerator::global()->bounded(2, 5);

    qreal altoEscena = escena->height();
    qreal mitad = altoEscena / 2.0;
    qreal centroArriba = mitad / 2.0;
    qreal centroAbajo = mitad + centroArriba;

    for (int i = 0; i < cantidad; ++i) {
        EnemigoVolador *enemigo = new EnemigoVolador();

        qreal yPos = (i % 2 == 0) ? centroAbajo : centroArriba;

        enemigo->setPos(2100 + i * 40, yPos);
        enemigo->establecerYInicial(yPos);
        escena->addItem(enemigo);
        enemigos.append(enemigo);
    }
    timerGeneradorEnemigos->start(QRandomGenerator::global()->bounded(1500, 3501));
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
        if (Proyectil* p = dynamic_cast<Proyectil*>(item)) {
            if (!p->esDeGoku()) {
                goku->recibirDanio(10);
                escena->removeItem(p);
                proyectiles.removeOne(p);
                delete p;
                if (goku->getVida() <= 0) {
                    QMessageBox::information(this, "Fin del juego", "Goku ha sido derrotado");
                    close();
                    return;
                }
            }
        }
        if (EsferaDragon* esf = dynamic_cast<EsferaDragon*>(item)) {
            goku->curarCompleto();
            escena->removeItem(esf);
            if (esfera == esf) esfera = nullptr;
            delete esf;
        }
        if (MetaFinal* meta = dynamic_cast<MetaFinal*>(item)) {
                if (timer) timer->stop();
                if (timerEnemigos) timerEnemigos->stop();
                if (timerGeneradorEnemigos) timerGeneradorEnemigos->stop();
                if (timerColisiones) timerColisiones->stop();

            DialogoRetro dialog(this);
            dialog.exec();

            emit nivelCompletado();
            close();
            return;
        }
        if (Tenshinhan* jefe = dynamic_cast<Tenshinhan*>(item)) {
            QMessageBox::information(this, "Batalla", "\u00a1Tenshinhan aparece!");
            // Aquí podría iniciar una batalla real
        }
    }

    if (proyectilGoku) {
        QList<QGraphicsItem*> colP = proyectilGoku->collidingItems();
        for (QGraphicsItem* obj : colP) {
            EnemigoVolador* enemigo = dynamic_cast<EnemigoVolador*>(obj);
            if (enemigo) {
                escena->removeItem(enemigo);
                enemigos.removeOne(enemigo);
                delete enemigo;
                escena->removeItem(proyectilGoku);
                proyectiles.removeOne(proyectilGoku);
                delete proyectilGoku;
                proyectilGoku = nullptr;
                break;
            }
            if (tenshinhan && obj == tenshinhan) {
                tenshinhan->recibirDanio(10);
                escena->removeItem(proyectilGoku);
                proyectiles.removeOne(proyectilGoku);
                delete proyectilGoku;
                proyectilGoku = nullptr;
                break;
            }
        }
    }
}


void MainWindow::actualizarJuego()
{
    if (!goku) return;
    if (nivelActual == 1)
        goku->actualizarFisica();
    actualizarCamara();
}

void MainWindow::actualizarCamara(){
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
    if (hudTenshinhan) {
        int xHud = view->viewport()->width() - hudTenshinhan->rect().width() - 120;
        hudTenshinhan->setPos(view->mapToScene(QPoint(xHud, 30)));
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

void MainWindow::lanzarProyectiles()
{
    if (!tenshinhan) return;

    tenshinhan->animarAtaque();
    QVector<int> indices;
    if (patronAlterno) {
        indices << 1 << 2; // carriles 3 y 2
    } else {
        indices << 3 << 0; // carriles 1 y 4
    }
    patronAlterno = !patronAlterno;
    for (int idx : indices) {
            if (idx >= 0 && idx < carriles.size()) {
                Proyectil *p = new Proyectil(Proyectil::DeEnemigo, goku);
            p->setPos(tenshinhan->x(), carriles[idx]);
                escena->addItem(p);
                proyectiles.append(p);
        }
    }
}
