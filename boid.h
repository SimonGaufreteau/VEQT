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

    bool operator==(Boid comp);
    bool operator!=(Boid comp);
};

#endif // BOID_H
