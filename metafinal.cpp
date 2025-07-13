#include "metafinal.h"
#include <QPixmap>

MetaFinal::MetaFinal(QGraphicsItem *parent)
 : QGraphicsPixmapItem(parent)
{
    QPixmap pix(40, 40);
    pix.fill(Qt::yellow);
    setPixmap(pix);
}
