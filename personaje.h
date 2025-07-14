#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Personaje(int vidaInicial = 100, QObject *parent = nullptr);

    int getVida() const { return vida; }

signals:
    void vidaActualizada(int nuevaVida);
    void derrotado();

public slots:
    virtual void recibirDanio(int cantidad);
    virtual void curarCompleto();

protected:
    int vida;
};

#endif // PERSONAJE_H
