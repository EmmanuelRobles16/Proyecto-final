#include "goku.h"
#include <QPixmap>

Goku::Goku()
{
    QPixmap sprite(":/sprites/goku.png");
    setPixmap(sprite.scaled(60, 60));
    velocidad = 5;
    vida = 100;
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
    setPos(x(), y() - 50);
}
