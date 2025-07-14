#include "enemigovolador.h"
#include <QPixmap>
#include <QtMath>
#include <QtGlobal>
#include <QGraphicsScene>

EnemigoVolador::EnemigoVolador(QObject *parent)
    : QObject(parent)
{
    QPixmap sprite(":/sprites/enemigo_volador.png");
    setPixmap(sprite.scaled(60, 60));

    velocidadX = -19.0f;
    yInicial = 0.0f;
    amplitud = 150.0f;
    frecuencia = 0.5f;
    tiempo = 0.0f;
}

void EnemigoVolador::actualizarMovimiento()
{
    tiempo += 0.1f;
    qreal nuevaY = yInicial + amplitud * qSin(frecuencia * tiempo);
    qreal maxY = scene() ? scene()->height() - boundingRect().height() : 600 - boundingRect().height();
    nuevaY = qBound(0.0, nuevaY, maxY);
    setPos(x() + velocidadX, nuevaY);
}

bool EnemigoVolador::estaFueraDePantalla() const
{
    return x() < -pixmap().width();
}
