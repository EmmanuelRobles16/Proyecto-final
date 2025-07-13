#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <QGraphicsRectItem>
#include <QObject>

#include <QGraphicsPixmapItem>
#include <QObject>

    class Plataforma : public QGraphicsPixmapItem
{
    public:
    Plataforma(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
};

#endif // PLATAFORMA_H
