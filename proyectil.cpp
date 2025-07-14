#include "proyectil.h"
#include "goku.h"
#include <QGraphicsScene>

Proyectil::Proyectil(Tipo t, Goku *objetivo, QObject *parent)
    : QObject(parent), tipo(t), goku(objetivo)
{
    velocidadX = (tipo == DeGoku) ? 15.0 : -15.0;

    QPixmap sprite(tipo == DeGoku ? ":/sprites/ataque_goku.png" : ":/sprites/rayo.png");
    setPixmap(sprite.scaled(20, 20));
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    connect(&timerMovimiento, &QTimer::timeout, this, &Proyectil::mover);
    timerMovimiento.start(30);
}

void Proyectil::mover()
{
    setX(x() + velocidadX);

    if (scene()) {
        if (x() + boundingRect().width() < 0 || x() > scene()->width()) {
            emit eliminado(this);
            scene()->removeItem(this);
            deleteLater();
            return;
        }
    }

    if (tipo == DeEnemigo) {
        QList<QGraphicsItem*> colisiones = collidingItems();
        for (QGraphicsItem* item : colisiones) {
            Goku* g = dynamic_cast<Goku*>(item);
            if (g && goku == g) {
                goku->recibirDanio(10);
                emit eliminado(this);
                if (scene())
                    scene()->removeItem(this);
                deleteLater();
                return;
            }
        }
    }
}
