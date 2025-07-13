#include "plataforma.h"
#include <QPixmap>
#include <QGraphicsScene>

Plataforma::Plataforma(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
        QPixmap sprite(":/sprites/plataforma.png");
    setPixmap(sprite.scaled(width, height));
    setPos(x, y);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
}
