#ifndef MENU_H
#define MENU_H

#include <QWidget>

namespace Ui {
class Menu;
}

class Menu : public QWidget {
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

signals:
    void nivelSeleccionado(int numero);  // Envia señal al main

private slots:
    void on_btnNivel1_clicked();
    void on_btnNivel2_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
