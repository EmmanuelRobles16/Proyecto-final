#ifndef GOKU_H
#define GOKU_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QVector>
#include <QTimer>
#include <QtMultimedia/QSoundEffect>
#include "personaje.h"

class Goku : public Personaje
{
    Q_OBJECT
public:
    explicit Goku(QObject *parent = nullptr);
signals:
    void ataqueLanzado();

public slots:
    void recibirDanio(int cantidad);
    void curarCompleto();

    void moverIzquierda();
    void moverDerecha();
    void saltar();
    void actualizarFisica();
    void activarPlaneo();
    void desactivarPlaneo();
    void detenerAnimacionCaminar();
    void atacar();
    bool estaEnElAire() const { return enElAire;}

private:
    void actualizarHUD();

    void iniciarAnimacionCaminar();
    void actualizarFrameCaminar();

    float velocidadX;
    float velocidadY;
    float gravedad;
    float gravedadNormal;
    float gravedadSuave;
    bool enElAire;
    bool estaPlaneando;
    int framesPlaneo;
    int maxFramesPlaneo;

    QVector<QPixmap> spritesCaminar;
    QPixmap spriteIdle;
    QPixmap spritePlaneo;
    QPixmap spriteAntesAtaque;
    QPixmap spriteAtaque;

    bool puedeAtacar;

    QTimer animacionTimer;
    int frameActual;
    bool caminando;

    QSoundEffect sonidoGolpe;
};


#endif // GOKU_H
