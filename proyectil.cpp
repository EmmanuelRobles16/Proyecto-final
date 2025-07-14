#include "proyectil.h"
#include "goku.h"
#include <QGraphicsScene>

Proyectil::Proyectil(Goku *objetivo, QObject *parent)
    : QObject(parent), goku(objetivo), velocidadX(-15.0)
{
    QPixmap sprite(":/sprites/rayo.png");
    setPixmap(sprite.scaled(40, 40));
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    connect(&timerMovimiento, &QTimer::timeout, this, &Proyectil::mover);
    timerMovimiento.start(30);
}

void Proyectil::mover()
{
    setX(x() + velocidadX);

    if (scene() && x() + boundingRect().width() < 0) {
        scene()->removeItem(this);
        deleteLater();
        return;
    }

    QList<QGraphicsItem*> colisiones = collidingItems();
    for (QGraphicsItem* item : colisiones) {
        Goku* g = dynamic_cast<Goku*>(item);
        if (g && goku == g) {
            goku->recibirDanio(10);
            if (scene())
                scene()->removeItem(this);
            deleteLater();
            return;
        }
    }
}
