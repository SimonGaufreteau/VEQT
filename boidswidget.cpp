#include "boidswidget.h"
#include <QDebug>

BoidsWidget::BoidsWidget(QWidget *parent) : QWidget(parent),m_timer(this)
{
     for(int i=0;i<listSize;i++){
         QPoint position(rand()%(parent->width()),rand()%(parent->height()));
         int signY,signX;
         signY=rand()%2?-1:1;
         signX=rand()%2?-1:1;
         QVector2D velocity(signX*(float)(rand()%100)/100,signY*(float)(rand()%100)/100);
         Boid tempBoid(position,velocity);
         boidList.append(tempBoid);
     }
     m_timer.setInterval(time);
     m_timer.start();
     connect(&m_timer,SIGNAL(timeout()),this,SLOT(paintMoveBoids()));
}

void BoidsWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    //BG : (253,243,255)
    painter.fillRect(rect(),QBrush(QColor(253,243,255)));

    for(int i=0;i<listSize;i++){
        Boid tempBoid = boidList[i];
        //Setting the shape for the boid and drawing it
        //New method for an oriented triangle
        QPainterPath path;

        qreal angle = qAtan2(tempBoid.velocity.x(),tempBoid.velocity.y());
        qreal newX = qCos(angle)*boidHeight+tempBoid.position.x();
        qreal newY = qSin(angle)*boidHeight+tempBoid.position.y();
        path.moveTo(newX,newY);

        //Line from velocity to the second point on the triangle
        qreal angle2 = angle+M_PI_2;
        qreal newX2 = tempBoid.position.x() + qCos(angle2)*boidWidth;
        qreal newY2 = tempBoid.position.y() +qSin(angle2)*boidWidth;
        path.lineTo(newX2,newY2);

        angle2 = angle-M_PI_2;
        newX2 = tempBoid.position.x() + qCos(angle2)*boidWidth;
        newY2 = tempBoid.position.y() +qSin(angle2)*boidWidth;
        path.lineTo(newX2,newY2);
        path.lineTo(newX,newY);

        //Boid : (194,40,231)
        painter.setBrush(QBrush(QColor(194,40,231)));
        painter.drawPath(path);
    }
}

void BoidsWidget::paintMoveBoids(){
    repaint();
    move_boids();
}



void BoidsWidget::move_boids(){
    QVector2D v1(0,0),v2(0,0),v3(0,0);
    for(int i=0;i<boidList.length();i++){
        Boid* b = &boidList[i];
        v1 = cohesion(*b);
        v2 = alignment(*b);
        v3 = separation(*b);

        b->velocity += v1 + v2 + v3;

        //Checking for the max velocity
        if(b->velocity.x()>max_velocity || b->velocity.x()<-max_velocity)b->velocity.setX(b->velocity.x()*maxVelocityRatio);
        if(b->velocity.y()>max_velocity || b->velocity.y()<-max_velocity)b->velocity.setY(b->velocity.y()*maxVelocityRatio);

        b->position.setX(b->position.x()+b->velocity.x());
        b->position.setY(b->position.y()+b->velocity.y());        

        //Moving the boids to the opposite side of the screen
        if(b->position.x()>this->width())
            b->position.setX(0);
        else if(b->position.x()<0)
            b->position.setX(this->width());

        if(b->position.y()>this->height())
            b->position.setY(0);
        else if(b->position.y()<0)
            b->position.setY(this->height());

        //qDebug() << "i =  "<< i << " / boid : " << b->toString();
    }

}

//This rule describes how a boid will try to fly towards the centre of mass of neighbouring boids.
//For now all the boids are taken into account. TODO : only take the neighbours
QVector2D BoidsWidget::cohesion(Boid b){
    QVector2D center(0,0);
    int count=0;

    //Calculating the centre of mass of all other boids
    for(int i=0;i<boidList.length();i++){
        Boid tempBoid = boidList[i];
        if(b!=tempBoid){
            qreal tempDistance = qSqrt(qPow(b.position.x()-tempBoid.position.x(),2)+qPow(b.position.y()-tempBoid.position.y(),2));
            if(tempDistance<distance){
                center.setX(center.x()+tempBoid.position.x());
                center.setY(center.y()+tempBoid.position.y());
                count++;
            }
        }
    }
    //If there are no boids around, don't change the velocity
    if(count==0)
        return QVector2D(0,0);

    center/=count;

    //Setting the result to make the boid move towards this centre by a certain %
    center.setX(center.x()-b.position.x());
    center.setY(center.y()-b.position.y());

    return center/cohesionRatio;
}

//This rule describes how a boid will try to match velocity with near boids.
//Same code as 'cohesion' but taking velocity instead of position for the mean
QVector2D BoidsWidget::alignment(Boid b){
    QVector2D center;
    int count=0;

    for(int i=0;i<boidList.length();i++){
            Boid tempBoid = boidList[i];
            if(b!=tempBoid){
                qreal tempDistance = qSqrt(qPow(b.position.x()-tempBoid.position.x(),2)+qPow(b.position.y()-tempBoid.position.y(),2));
                if(tempDistance<distance){
                    center.setX(center.x()+tempBoid.position.x());
                    center.setY(center.y()+tempBoid.position.y());
                    count++;
                }
            }
        }
        //If there are no boids around, don't change the velocity
        if(count==0)
            return QVector2D(0,0);

        center/=count;

        //Setting the result to make the boid move towards this centre by a certain %
        center.setX(center.x()-b.position.x());
        center.setY(center.y()-b.position.y());

        return center/alignementRatio;

}

//This rule describes how a boid will try to keep a small distance away from other objects.
//For now this rule only checks the distance with other boids. TODO : angle checking.
QVector2D BoidsWidget::separation(Boid b){
    QVector2D result(0,0);
    for(int i=0;i<boidList.length();i++){
        Boid tempBoid = boidList[i];
        if(&b!=&tempBoid){
            if(qSqrt(qPow(b.position.x()-tempBoid.position.x(),2)+qPow(b.position.y()-tempBoid.position.y(),2))<separationDistance){
                result.setX(result.x()-(tempBoid.position.x()-b.position.x()));
                result.setY(result.y()-(tempBoid.position.y()-b.position.y()));
            }
        }
    }
    return result/separationRatio;
}

BoidsWidget::~BoidsWidget(){
}

