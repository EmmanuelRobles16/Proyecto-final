#include "esferadragon.h"
#include <QPixmap>

EsferaDragon::EsferaDragon()
{
    QPixmap sprite(":/sprites/esfera.png");
    setPixmap(sprite.scaled(70, 70));
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
}
