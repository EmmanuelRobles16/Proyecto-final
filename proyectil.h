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
    explicit Proyectil(Goku *objetivo, QObject *parent = nullptr);

private slots:
    void mover();

private:
    Goku *goku;
    qreal velocidadX;
    QTimer timerMovimiento;
};

#endif // PROYECTIL_H
