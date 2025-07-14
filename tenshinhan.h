#ifndef TENSHINHAN_H
#define TENSHINHAN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
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
    void derrotado();

public slots:
    void recibirDanio(int cantidad);
    void animarAtaque();

private:
    int vida;
    HUD *hud;
    QPixmap spriteIdle;
    QPixmap spriteAntesAtaque;
    QPixmap spriteAtaque;
};

#endif // TENSHINHAN_H
