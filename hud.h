#ifndef HUD_H
#define HUD_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QColor>

class HUD : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    explicit HUD(int ancho = 200, const QColor &color = Qt::green, QGraphicsItem *parent = nullptr);
public slots:
    void actualizar(int vida);
private:
    int anchoMax;
    QColor colorBarra;
    QGraphicsRectItem *barra;
};

#endif // HUD_H
