#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsItem>
#include "goku.h"
#include "enemigovolador.h"
#include "hud.h"
#include "plataforma.h"
#include "tenshinhan.h"
#include "proyectil.h"
#include "metafinal.h"
#include "esferadragon.h"
#include "dialogoretro.h"
#include <QVector>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
    explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    void iniciarNivel(int numero);
signals:
        void nivelCompletado();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
private slots:
    void actualizarEnemigos();
    void crearEnemigo();
    void verificarColisiones();
    void actualizarJuego();
    void actualizarCamara();
    void lanzarProyectiles();
private:
    void limitarX(QGraphicsItem *item, qreal minX, qreal maxX);
    Ui::MainWindow *ui;
    QGraphicsScene *escena = nullptr;
    Goku *goku = nullptr;
    QTimer *timer = nullptr;
    QVector<EnemigoVolador*> enemigos;
    QVector<Plataforma*> Plataformas;
    MetaFinal *metaFinal = nullptr;
    Tenshinhan *tenshinhan = nullptr;
    EsferaDragon *esfera = nullptr;
    QTimer *timerEnemigos = nullptr;
    QTimer *timerGeneradorEnemigos = nullptr;
    QTimer *timerColisiones = nullptr;
    QTimer *timerAtaqueTenshinhan = nullptr;
    HUD *hud = nullptr;
    HUD *hudTenshinhan = nullptr;
    QMediaPlayer *musicaFondo = nullptr;
    QAudioOutput *audioOutput = nullptr;
    int nivelActual = 0;
    QVector<int> carriles;
    int indiceCarril = 0;
    bool patronAlterno = false;
    QVector<Proyectil*> proyectiles;
    Proyectil *proyectilGoku = nullptr;
};


#endif // MAINWINDOW_H
