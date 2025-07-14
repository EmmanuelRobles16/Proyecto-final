#include "hud.h"
#include <QBrush>
#include <QPen>

HUD::HUD(int ancho, const QColor &color, QGraphicsItem *parent)
    : QObject(), QGraphicsRectItem(parent), anchoMax(ancho), colorBarra(color) {
    setRect(0, 0, anchoMax, 20);
        setPen(QPen(Qt::white));
        setBrush(Qt::NoBrush);

        barra = new QGraphicsRectItem(this);
        barra->setRect(0, 0, anchoMax, 20);
        barra->setBrush(colorBarra);
    barra->setPen(Qt::NoPen);
}

void HUD::actualizar(int vida) {
    if (vida < 0)
        vida = 0;
    qreal porcentaje = static_cast<qreal>(vida) / 100.0;
    barra->setRect(0, 0, anchoMax * porcentaje, rect().height());
}
