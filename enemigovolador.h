#ifndef ENEMIGOVOLADOR_H
#define ENEMIGOVOLADOR_H

#include <QObject>
#include <QGraphicsPixmapItem>

class EnemigoVolador : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit EnemigoVolador(QObject *parent = nullptr);

    void actualizarMovimiento();
    bool estaFueraDePantalla() const;

    void establecerYInicial(float valor) { yInicial = valor; }

private:
    float velocidadX;
    float yInicial;
    float amplitud;
    float frecuencia;
    float tiempo;
};

#endif // ENEMIGOVOLADOR_H
