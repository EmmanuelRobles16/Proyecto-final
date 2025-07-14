#include "goku.h"
#include "plataforma.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QtMultimedia/QSoundEffect>
#include <QtGlobal>
Goku::Goku(QObject *parent)
    : Personaje(100, parent)
{
    spriteIdle = QPixmap(":/sprites/goku_idle.png");
    spritePlaneo = QPixmap(":/sprites/goku_planeando.png");
    spriteAntesAtaque = QPixmap(":/sprites/goku_antes_de_atacar.png");
    spriteAtaque = QPixmap(":/sprites/goku_atacando.png");
    spritesCaminar.append(QPixmap(":/sprites/goku_walk1.png"));
    spritesCaminar.append(QPixmap(":/sprites/goku_walk2.png"));
    spritesCaminar.append(QPixmap(":/sprites/goku_walk3.png"));

    setPixmap(spriteIdle.scaled(60, 60));
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    connect(&animacionTimer, &QTimer::timeout, this, &Goku::actualizarFrameCaminar);
    animacionTimer.setInterval(150);
    frameActual = 0;
    caminando = false;

    puedeAtacar = true;

    sonidoGolpe.setSource(QUrl("qrc:/audio/golpe.wav"));
    sonidoGolpe.setVolume(0.8);

    velocidadX = 0.0f;
    velocidadY = 0.0f;
    gravedadNormal = 1.5f;
    gravedadSuave = gravedadNormal / 4.0f;
    gravedad = gravedadNormal;
    enElAire = false;
    estaPlaneando = false;
    framesPlaneo = 0;
    maxFramesPlaneo = 60;

    actualizarHUD();
}

void Goku::moverIzquierda()
{
    if (enElAire) {
        velocidadX = -5.0f;
    } else {
        qreal nuevaX = x() - 5;
        qreal minX = 0;
        qreal maxX = scene() ? scene()->width() - boundingRect().width() : 800 - boundingRect().width();
        setX(qBound(minX, nuevaX, maxX));
    }
    iniciarAnimacionCaminar();
}

void Goku::moverDerecha()
{
    if (enElAire) {
        velocidadX = 5.0f;
    } else {
        qreal nuevaX = x() + 5;
        qreal minX = 0;
        qreal maxX = scene() ? scene()->width() - boundingRect().width() : 800 - boundingRect().width();
        setX(qBound(minX, nuevaX, maxX));
    }
    iniciarAnimacionCaminar();
}
void Goku::saltar()
{
    if (!enElAire) {
        velocidadY = -20.0f;
        enElAire = true;
    }
}

void Goku::activarPlaneo()
{
    if (enElAire && !estaPlaneando) {
        gravedad = gravedadSuave;
        estaPlaneando = true;
        framesPlaneo = 0;
        if (velocidadY > 4.0f) {
            velocidadY = 4.0f;
        }
        setPixmap(spritePlaneo.scaled(60, 60));
    }
}

void Goku::desactivarPlaneo()
{
    if (estaPlaneando) {
        gravedad = gravedadNormal;
        estaPlaneando = false;
        if (!caminando)
            setPixmap(spriteIdle.scaled(60, 60));
    }
}
void Goku::recibirDanio(int cantidad)
{
    sonidoGolpe.play();
    Personaje::recibirDanio(cantidad);
}
void Goku::curarCompleto()
{
    Personaje::curarCompleto();
}
void Goku::actualizarHUD()
{
    emit vidaActualizada(vida);
}
void Goku::actualizarFisica()
{
    // Posicion anterior para detectar aterrizajes
    qreal yAnterior = y();

    // Aplicar gravedad
    velocidadY += gravedad;
    if (estaPlaneando) {
        ++framesPlaneo;
        if (framesPlaneo >= maxFramesPlaneo) {
            desactivarPlaneo();
        }
    }

    // Actualizar posicion con velocidades actuales
    setPos(x() + velocidadX, y() + velocidadY);

    bool aterrizo = false;
    QList<QGraphicsItem*> items = collidingItems();
    for (QGraphicsItem* it : items) {
        Plataforma* plat = dynamic_cast<Plataforma*>(it);
        if (plat && velocidadY >= 0) {
            qreal top = plat->y();
            qreal gokuBottomPrev = yAnterior + boundingRect().height();
            if (gokuBottomPrev <= top + 1) {
                setPos(x(), top - boundingRect().height());
                velocidadY = 0.0f;
                velocidadX = 0.0f;
                enElAire = false;
                desactivarPlaneo();
                aterrizo = true;
                break;
            }
        }
    }

    // Verificar colision con el suelo si no aterrizo en plataforma
    if (!aterrizo && y() >= 500) {
        setPos(x(), 500);
        velocidadY = 0.0f;
        velocidadX = 0.0f;
        enElAire = false;
        desactivarPlaneo();
    } else if (!aterrizo) {
        enElAire = true;
    }

    // Mantener a Goku dentro de los limites de la escena
    if (scene()) {
        qreal maxX = scene()->width() - boundingRect().width();
        qreal maxSceneY = scene()->height() - boundingRect().height();
        qreal maxY = qMin(maxSceneY, 500.0);
        qreal boundedX = qBound(0.0, x(), maxX);
        qreal boundedY = qBound(0.0, y(), maxY);
        if (boundedY <= 0.0 && velocidadY < 0)
            velocidadY = 0.0f;
        setPos(boundedX, boundedY);
    }
}


void Goku::iniciarAnimacionCaminar()
{
    if (!caminando && !estaPlaneando) {
        caminando = true;
        frameActual = 0;
        animacionTimer.start();
    }
}

void Goku::detenerAnimacionCaminar()
{
    if (caminando) {
        caminando = false;
        animacionTimer.stop();
        if (!estaPlaneando)
            setPixmap(spriteIdle.scaled(60, 60));
    }
}
void Goku::actualizarFrameCaminar()
{
    if (!caminando || spritesCaminar.isEmpty())
        return;
    frameActual = (frameActual + 1) % spritesCaminar.size();
    setPixmap(spritesCaminar[frameActual].scaled(60, 60));
}

void Goku::atacar()
{
    if (!puedeAtacar)
        return;

    puedeAtacar = false;
    setPixmap(spriteAntesAtaque.scaled(60, 60));

    QTimer::singleShot(100, [this]() {
        setPixmap(spriteAtaque.scaled(60, 60));
        emit ataqueLanzado();
    });

    QTimer::singleShot(250, [this]() {
        setPixmap(spritesCaminar[0].scaled(60, 60));
    });

    QTimer::singleShot(400, [this]() {
        puedeAtacar = true;
    });
}
