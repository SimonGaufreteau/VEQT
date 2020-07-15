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
     ~BoidsWidget();
private:
    QTimer m_timer;
    QVector<Boid> boidList;

    static const int listSize = 5;
    static const int time =200;
    static const int boidWidth = 20;
    static const int boidHeight = 20;
    static const int cohesionRatio = 10;

    void move_boids();
    QVector2D cohesion(Boid b);
    QVector2D alignment(Boid b);
    QVector2D separation(Boid b);

private slots:
    void paintMoveBoids();

signals:

};

#endif // BOIDSWIDGET_H
