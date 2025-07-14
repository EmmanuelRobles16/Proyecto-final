#include "personaje.h"

Personaje::Personaje(int vidaInicial, QObject *parent)
    : QObject(parent), vida(vidaInicial)
{
}

void Personaje::recibirDanio(int cantidad)
{
    int vidaAnterior = vida;
    vida -= cantidad;
    if (vida < 0)
        vida = 0;
    emit vidaActualizada(vida);
    if (vidaAnterior > 0 && vida == 0)
        emit derrotado();
}

void Personaje::curarCompleto()
{
    vida = 100;
    emit vidaActualizada(vida);
}
