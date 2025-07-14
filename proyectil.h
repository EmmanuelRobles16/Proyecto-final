#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Goku;

class Proyectil : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum Tipo { DeEnemigo, DeGoku };

    explicit Proyectil(Tipo tipo, Goku *objetivo = nullptr, QObject *parent = nullptr);

    bool esDeGoku() const { return tipo == DeGoku; }

signals:
    void eliminado(Proyectil* p);

private slots:
    void mover();

private:
    Tipo tipo;
    Goku *goku;
    qreal velocidadX;
    QTimer timerMovimiento;
};

#endif // PROYECTIL_H
