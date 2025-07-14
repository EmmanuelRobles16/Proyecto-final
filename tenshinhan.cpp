#include "tenshinhan.h"
#include <QPixmap>

Tenshinhan::Tenshinhan(QObject *parent)
    : QObject(parent), vida(300), hud(nullptr)
{
    QPixmap sprite(":/sprites/tenshinhan.png");
    setPixmap(sprite.scaled(80, 80));
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    setPos(760, 200); // fixed position on the right edge

    hud = new HUD(600, Qt::red, this);
    hud->setZValue(1);
    hud->setPos(boundingRect().width()/2 - hud->rect().width()/2, -25);
    hud->actualizar(vida);
}

void Tenshinhan::recibirDanio(int cantidad)
{
    vida -= cantidad;
    if (vida < 0)
        vida = 0;
    emit vidaActualizada(vida);
    if (hud)
        hud->actualizar(vida);
}
