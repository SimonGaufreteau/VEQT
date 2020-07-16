#ifndef BOIDSWIDGET_H
#define BOIDSWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QPainterPath>
#include <QtMath>
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

    static const int listSize = 20;
    static const int time = 10;
    static const int boidWidth = 20;
    static const int boidHeight = 20;
    static const int cohesionRatio = 800;
    static const int separationRatio = 300;
    static const int wallRatio = 80;
    static const int wallDistance = 100;
    static const int distance = 150;
    static const int max_velocity = 2;
    static constexpr float velocity_ratio = 0.8f;

    void move_boids();
    QVector2D cohesion(Boid b);
    QVector2D alignment(Boid b);
    QVector2D separation(Boid b);

private slots:
    void paintMoveBoids();

signals:

};

#endif // BOIDSWIDGET_H
