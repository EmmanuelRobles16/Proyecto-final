#ifndef GOKU_H
#define GOKU_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Goku : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Goku();

    void moverIzquierda();
    void moverDerecha();
    void saltar();

private:
    int velocidad;
    int vida;
};

#endif // GOKU_H
