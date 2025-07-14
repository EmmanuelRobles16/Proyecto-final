#include "tenshinhan.h"
#include <QPixmap>

Tenshinhan::Tenshinhan(QObject *parent)
    : QObject(parent), vida(300), hud(nullptr)
{
    QPixmap sprite(":/sprites/tenshinhan.png");
    setPixmap(sprite.scaled(80, 80));
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    // Ubicar a Tenshinhan al mismo nivel que Goku
    setPos(650, 450);

    // HUD más pequeño centrado sobre el personaje
    // HUD pequeño (no dependiente del personaje)
    hud = new HUD(80, Qt::red);
    hud->setZValue(10);
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
