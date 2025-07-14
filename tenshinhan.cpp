#include "tenshinhan.h"
#include <QPixmap>
#include <QTimer>

Tenshinhan::Tenshinhan(QObject *parent)
    : QObject(parent), vida(300), hud(nullptr)
{
    spriteIdle = QPixmap(":/sprites/tenshinhan_idle.png");
    spriteAntesAtaque = QPixmap(":/sprites/tenshinhan_antes.png");
    spriteAtaque = QPixmap(":/sprites/tenshinhan_atacando.png");

    setPixmap(spriteIdle.scaled(80, 80));
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    // Ubicar a Tenshinhan al mismo nivel que Goku
    setPos(650, 450);

    // HUD más pequeño centrado sobre el personaje
    // HUD pequeño (no dependiente del personaje)
    hud = new HUD(80, Qt::red);
    hud->setZValue(10);
    hud->actualizar(vida);
}

void Tenshinhan::animarAtaque()
{
    setPixmap(spriteAntesAtaque.scaled(80, 80));
    QTimer::singleShot(150, [this]() {
        setPixmap(spriteAtaque.scaled(80, 80));
    });
    QTimer::singleShot(300, [this]() {
        setPixmap(spriteIdle.scaled(80, 80));
    });
}

void Tenshinhan::recibirDanio(int cantidad)
{
    vida -= cantidad;
    if (vida < 0)
        vida = 0;
    emit vidaActualizada(vida);
    if (hud)
        hud->actualizar(vida);
}
