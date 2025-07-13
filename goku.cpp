#include "goku.h"
#include <QPixmap>
#include <QGraphicsScene>

Goku::Goku(QObject *parent)
    : QObject(parent)
{
        QPixmap sprite(":/sprites/goku.png");
        setPixmap(sprite.scaled(60, 60));

    velocidadX = 0.0f;
    velocidadY = 0.0f;
    gravedadNormal = 1.5f;
    gravedadSuave = gravedadNormal / 4.0f;
    gravedad = gravedadNormal;
    enElAire = false;
    estaPlaneando = false;
    framesPlaneo = 0;
    maxFramesPlaneo = 60;
    vida = 100;

    actualizarHUD();
}

void Goku::moverIzquierda()
{
    if (enElAire) {
        velocidadX = -5.0f;
    } else {
        qreal nuevaX = x() - 5;
        if (nuevaX < 0)
            nuevaX = 0;
        setX(nuevaX);
    }
}

void Goku::moverDerecha()
{
    if (enElAire) {
        velocidadX = 5.0f;
    } else {
        qreal limite = scene() ? scene()->width() - boundingRect().width() : x() + 5;
        qreal nuevaX = x() + 5;
        if (scene() && nuevaX > limite)
            nuevaX = limite;
        setX(nuevaX);
    }
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
    }
}

void Goku::desactivarPlaneo()
{
    if (estaPlaneando) {
        gravedad = gravedadNormal;
        estaPlaneando = false;
    }
}

void Goku::recibirDanio(int cantidad)
{
    vida -= cantidad;
    if (vida < 0) {
        vida = 0;
    }
    actualizarHUD();
}

void Goku::actualizarHUD()
{
    emit vidaActualizada(vida);
}
void Goku::actualizarFisica()
{
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

    // Verificar colision con el suelo
    if (y() >= 500) {
        setPos(x(), 500);
        velocidadY = 0.0f;
        velocidadX = 0.0f;
        enElAire = false;
        desactivarPlaneo();
    }
}
