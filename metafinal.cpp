#include "metafinal.h"
#include <QPixmap>

MetaFinal::MetaFinal()
{
    QPixmap pix(40, 40);
    pix.fill(Qt::yellow);
    setPixmap(pix);
}
