#include "boid.h"
#include <iostream>

Boid::Boid(QPoint basePosition,QVector2D baseVelocity):position(basePosition),velocity(baseVelocity)
{
}

QString Boid::toString(){
    return QString("Position : x = %1, y = %2 / Velocity : x = %3, y = %4").arg(position.x()).arg(position.y()).arg(velocity.x()).arg(velocity.y());
}

bool Boid::operator==(Boid comp){
    return comp.position==this->position && comp.velocity==this->velocity;
}

bool Boid::operator!=(Boid comp){
    return !operator==(comp);
}
