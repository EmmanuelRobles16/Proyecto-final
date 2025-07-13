#include "goku.h"
#include <QPixmap>

Goku::Goku(QObject *parent)
    : QObject(parent)
{
    QPixmap sprite(":/sprites/goku.png");
    setPixmap(sprite.scaled(60, 60));
    velocidad = 5;
    vida = 100;

    velocidadY = 0.0f;
    gravedad = 1.0f;
    enElAire = false;
}
void Goku::moverIzquierda()
{
    setPos(x() - velocidad, y());
}
void Goku::moverDerecha()
{
    setPos(x() + velocidad, y());
}

void Goku::saltar()
{
    if (!enElAire) {
        velocidadY = -15.0f;
        enElAire = true;
    }
}

void Goku::actualizarFisica()
{
    velocidadY += gravedad;
    setPos(x(), y() + velocidadY);

    if (y() >= 500) {
        setPos(x(), 500);
        velocidadY = 0.0f;
        enElAire = false;
    }
}
