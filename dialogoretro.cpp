#include "dialogoretro.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>

DialogoRetro::DialogoRetro(QWidget *parent)
    : QDialog(parent)
{
    setModal(true);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setStyleSheet("background-color: black; border: 2px solid white; color: white;");

    QLabel *krilin = new QLabel(this);
    krilin->setPixmap(QPixmap(":/sprites/krilin.png").scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QLabel *goku = new QLabel(this);
    goku->setPixmap(QPixmap(":/sprites/goku.png").scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QLabel *texto = new QLabel(tr("Bien hecho Goku"), this);
    texto->setAlignment(Qt::AlignCenter);

    QPushButton *boton = new QPushButton(tr("Continuar"), this);
    boton->setStyleSheet("background-color: black; color: white; border: 1px solid white;");

    QVBoxLayout *centro = new QVBoxLayout;
    centro->addWidget(texto);
    centro->addWidget(boton, 0, Qt::AlignCenter);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(krilin);
    layout->addLayout(centro);
    layout->addWidget(goku);

    connect(boton, &QPushButton::clicked, this, &DialogoRetro::accept);
}
