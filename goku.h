#ifndef GOKU_H
#define GOKU_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Goku : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Goku(QObject *parent = nullptr);

    int getVida() const { return vida; }

signals:
    void vidaActualizada(int nuevaVida);

public slots:
    void recibirDanio(int cantidad);
    void curarCompleto();

    void moverIzquierda();
    void moverDerecha();
    void saltar();
    void actualizarFisica();
    void activarPlaneo();
    void desactivarPlaneo();
    bool estaEnElAire() const { return enElAire; }

private:
    void actualizarHUD();

    float velocidadX;
    float velocidadY;
    float gravedad;
    float gravedadNormal;
    float gravedadSuave;
    bool enElAire;
    bool estaPlaneando;
    int framesPlaneo;
    int maxFramesPlaneo;
    int vida;
};


#endif // GOKU_H
