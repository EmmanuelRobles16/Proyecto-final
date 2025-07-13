#include "metafinal.h"
#include <QPixmap>

MetaFinal::MetaFinal()
{
    QPixmap sprite(":/sprites/krilin.png");
    // Utilizar a Krilin como indicador de meta
    setPixmap(sprite.scaled(80, 60));
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
}
