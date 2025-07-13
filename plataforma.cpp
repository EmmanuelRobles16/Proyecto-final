#include "plataforma.h"
#include <QBrush>
#include <QPen>

Plataforma::Plataforma(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{
    setRect(0, 0, width, height);
    setPos(x, y);
    setBrush(QBrush(Qt::darkGray));
    setPen(QPen(Qt::NoPen));
}
