#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <QGraphicsRectItem>
#include <QObject>

class Plataforma : public QGraphicsRectItem
{
public:
    Plataforma(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
};

#endif // PLATAFORMA_H
