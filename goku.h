#ifndef GOKU_H
#define GOKU_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Goku : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Goku(QObject *parent = nullptr);

    void moverIzquierda();
    void moverDerecha();
    void saltar();
    void actualizarFisica();

private:
    int velocidad;
    int vida;

    float velocidadY;
    float gravedad;
    bool enElAire;
};

#endif // GOKU_H
