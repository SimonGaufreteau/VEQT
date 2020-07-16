#include "boidswidget.h"
#include <QDebug>

BoidsWidget::BoidsWidget(QWidget *parent) : QWidget(parent),m_timer(this)
{
     for(int i=0;i<listSize;i++){
         QPoint position(rand()%(parent->width()),rand()%(parent->height()));
         QVector2D velocity(rand()%2+1,rand()%2+1);
         Boid tempBoid(position,velocity);
         boidList.append(tempBoid);
     }
     m_timer.setInterval(time);
     m_timer.start();
     connect(&m_timer,SIGNAL(timeout()),this,SLOT(paintMoveBoids()));
}

void BoidsWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    for(int i=0;i<listSize;i++){
        Boid tempBoid = boidList[i];
        //Setting the shape for the boid and drawing it
        QRectF rect = QRectF(tempBoid.position.x(), tempBoid.position.y(), boidWidth, boidHeight);
        QPainterPath path;
        path.moveTo(rect.left() + (rect.width() / 2), rect.top());
        path.lineTo(rect.bottomLeft());
        path.lineTo(rect.bottomRight());
        path.lineTo(rect.left() + (rect.width() / 2), rect.top());
        painter.fillPath(path, QBrush(QColor ("blue")));
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
        //v2 = alignment(*b);
        v3 = separation(*b);

        //qDebug() << "Cohesion : "<< v1 << " / Alignement : "<<v2 << " / Separation : "<<v3;
        b->velocity += v1 + v2 + v3;

        //Checking for the max velocity
        if(b->velocity.x()>max_velocity || b->velocity.x()<-max_velocity)b->velocity.setX(b->velocity.x()*maxVelocityRatio);
        if(b->velocity.y()>max_velocity || b->velocity.y()<-max_velocity)b->velocity.setY(b->velocity.y()*maxVelocityRatio);

        b->position.setX(b->position.x()+b->velocity.x());
        b->position.setY(b->position.y()+b->velocity.y());

        //Moving the boids off the wall if they come too close
        if(b->position.x()>this->width()-wallDistance)
            b->velocity.setX(b->velocity.x()-qAbs(b->position.x()-this->width())/wallRatio);
        else    if(b->position.x()<wallDistance)
            b->velocity.setX(b->velocity.x()+qAbs(b->position.x())/wallRatio);

        if(b->position.y()>this->height()-wallDistance)
            b->velocity.setY(b->velocity.y()-qAbs(b->position.y()-this->height())/wallRatio);
        else if(b->position.y()<wallDistance)
            b->velocity.setY(b->velocity.y()+qAbs(b->position.y())/wallRatio);

        //qDebug() << "i =  "<< i << " / boid : " << b->toString();
    }

}

//This rule describes how a boid will try to fly towards the centre of mass of neighbouring boids.
//For now all the boids are taken into account. TODO : only take the neighbours
QVector2D BoidsWidget::cohesion(Boid b){
    QVector2D center;
    int count=0;

    //Calculating the centre of mass of all other boids
    for(int i=0;i<boidList.length();i++){
        Boid tempBoid = boidList[i];
        if(b!=tempBoid){
            qreal tempDistance = qSqrt(qPow(b.position.x()-tempBoid.position.x(),2)+qPow(b.position.y()-tempBoid.position.y(),2));
            //qDebug() << "Distance : "<< tempDistance;
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

QVector2D BoidsWidget::alignment(Boid b){

}

//This rule describes how a boid will try to keep a small distance away from other objects.
//For now this rule only checks the distance with other boids. TODO : angle checking.
QVector2D BoidsWidget::separation(Boid b){
    QVector2D result(0,0);
    for(int i=0;i<boidList.length();i++){
        Boid tempBoid = boidList[i];
        if(&b!=&tempBoid){
            //qDebug() << qSqrt(qPow(b.position.x()-tempBoid.position.x(),2)+qPow(b.position.y()-tempBoid.position.y(),2));
            if(qSqrt(qPow(b.position.x()-tempBoid.position.x(),2)+qPow(b.position.y()-tempBoid.position.y(),2))<distance){
                result.setX(result.x()-(tempBoid.position.x()-b.position.x()));
                result.setY(result.y()-(tempBoid.position.y()-b.position.y()));
            }
        }
    }
    return result/separationRatio;
}

BoidsWidget::~BoidsWidget(){
    qDebug() << "Deleting the Boids";
}

