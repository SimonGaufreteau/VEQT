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

    static const int listSize = 100;
    static const int time = 10;
    static const int boidWidth = 5;
    static const int boidHeight = 20;
    static const int cohesionRatio = 1000;
    static const int separationRatio = 100;
    static const int alignementRatio = 2000;
    static const int distance = 100;
    static const int separationDistance=20;
    static constexpr float max_velocity = 2.5f;
    static constexpr float maxVelocityRatio = 0.6f;
    static constexpr float noiseRatio = 0.05f;

    void move_boids();
    QVector2D cohesion(Boid b);
    QVector2D alignment(Boid b);
    QVector2D separation(Boid b);
    QVector2D getNoise(Boid b);

private slots:
    void paintMoveBoids();

signals:

};

#endif // BOIDSWIDGET_H
