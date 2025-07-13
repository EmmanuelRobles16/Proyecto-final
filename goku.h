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
    void activarPlaneo();
    void desactivarPlaneo();
    bool estaEnElAire() const { return enElAire; }
private:
    float velocidadX;
    float velocidadY;
    float gravedad;
    float gravedadNormal;
    float gravedadSuave;
    bool enElAire;
    bool estaPlaneando;
    int framesPlaneo;
    int maxFramesPlaneo;
};

#endif // GOKU_H
