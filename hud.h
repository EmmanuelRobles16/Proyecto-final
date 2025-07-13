#ifndef HUD_H
#define HUD_H

#include <QObject>
#include <QGraphicsRectItem>

class HUD : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    explicit HUD(QGraphicsItem *parent = nullptr);
public slots:
    void actualizar(int vida);
private:
    int anchoMax;
    QGraphicsRectItem *barra;
};

#endif // HUD_H
