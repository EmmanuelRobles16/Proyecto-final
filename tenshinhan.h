#ifndef TENSHINHAN_H
#define TENSHINHAN_H

#include <QObject>//␊
#include "personaje.h"
#include <QPixmap>//␊
#include "hud.h"
class Tenshinhan : public Personaje
{
    Q_OBJECT
public:
    explicit Tenshinhan(QObject *parent = nullptr);

   HUD* getHUD() const { return hud; }

public slots:
    void recibirDanio(int cantidad);
    void animarAtaque();

private:
    HUD *hud;
    QPixmap spriteIdle;
    QPixmap spriteAntesAtaque;
    QPixmap spriteAtaque;
};

#endif // TENSHINHAN_H
