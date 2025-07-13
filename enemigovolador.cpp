#include "enemigovolador.h"
#include <QPixmap>
#include <QtMath>

EnemigoVolador::EnemigoVolador(QObject *parent)
    : QObject(parent)
{
    QPixmap sprite(":/sprites/enemigo_volador.png");
    setPixmap(sprite.scaled(60, 60));

    velocidadX = -3.0f;
    yInicial = 0.0f;
    amplitud = 40.0f;
    frecuencia = 0.1f;
    tiempo = 0.0f;
}

void EnemigoVolador::actualizarMovimiento()
{
    tiempo += 0.1f;
    setPos(x() + velocidadX, yInicial + amplitud * qSin(frecuencia * tiempo));
}

bool EnemigoVolador::estaFueraDePantalla() const
{
    return x() < -pixmap().width();
}
