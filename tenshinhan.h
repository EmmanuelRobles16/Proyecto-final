#ifndef TENSHINHAN_H
#define TENSHINHAN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "hud.h"

class Tenshinhan : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Tenshinhan(QObject *parent = nullptr);

    int getVida() const { return vida; }
    HUD* getHUD() const { return hud; }

signals:
    void vidaActualizada(int nuevaVida);

public slots:
    void recibirDanio(int cantidad);

private:
    int vida;
    HUD *hud;
};

#endif // TENSHINHAN_H
