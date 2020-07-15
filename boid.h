#ifndef BOID_H
#define BOID_H

#include "QVector2D"
#include "QPoint"

class Boid
{
public:
    Boid(QPoint position,QVector2D velocity);
    QString toString();
    QPoint position;
    QVector2D velocity;
};

#endif // BOID_H
