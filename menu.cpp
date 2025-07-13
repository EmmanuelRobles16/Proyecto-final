#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu() {
    delete ui;
}

void Menu::on_btnNivel1_clicked() {
    emit nivelSeleccionado(1);
    this->hide();
}

void Menu::on_btnNivel2_clicked() {
    emit nivelSeleccionado(2);
    this->hide();
}
