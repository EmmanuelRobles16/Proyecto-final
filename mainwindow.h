#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include "goku.h"
#include "enemigovolador.h"
#include "hud.h"
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
    explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    void iniciarNivel(int numero);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void actualizarEnemigos();
    void crearEnemigo();
    void verificarColisiones();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *escena = nullptr;
    Goku *goku = nullptr;
    QTimer *timer = nullptr;
    QVector<EnemigoVolador*> enemigos;
    QTimer *timerEnemigos = nullptr;
    QTimer *timerGeneradorEnemigos = nullptr;
    QTimer *timerColisiones = nullptr;
    HUD *hud = nullptr;
};

#endif // MAINWINDOW_H
