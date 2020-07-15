#ifndef BOIDSWIDGET_H
#define BOIDSWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QPainterPath>
#include "boid.h"

class BoidsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BoidsWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
private:
    QTimer m_timer;
    QVector<Boid> boidList;

    static const int listSize = 5;
    static const int time = 5;
    static const int boidWidth = 20;
    static const int boidHeight = 20;

    void move_boids();
    QVector2D cohesion();
    QVector2D alignment();
    QVector2D separation();

private slots:
    void paintMoveBoids();

signals:

};

#endif // BOIDSWIDGET_H
