#include "goku.h"
#include <QPixmap>

Goku::Goku(QObject *parent)
    : QObject(parent)
{
    QPixmap sprite(":/sprites/goku.png");
    setPixmap(sprite.scaled(60, 60));

    velocidadX = 0.0f;
    velocidadY = 0.0f;
    gravedad = 1.0f;
    enElAire = false;
}
void Goku::moverIzquierda()
{
    if (enElAire) {
        velocidadX = -5.0f;
    } else {
        setPos(x() - 5, y());
    }
}
void Goku::moverDerecha()
{
    if (enElAire) {
        velocidadX = 5.0f;
    } else {
        setPos(x() + 5, y());
    }
}

void Goku::saltar()
{
    if (!enElAire) {
        velocidadY = -20.0f;
        enElAire = true;
    }
}
void Goku::actualizarFisica()
{
    // Aplicar gravedad
    velocidadY += gravedad;

    // Actualizar posicion con velocidades actuales
    setPos(x() + velocidadX, y() + velocidadY);

    // Verificar colision con el suelo
    if (y() >= 500) {
        setPos(x(), 500);
        velocidadY = 0.0f;
        velocidadX = 0.0f;
        enElAire = false;
    }
}
