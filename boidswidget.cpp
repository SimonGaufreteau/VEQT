#include "boidswidget.h"
#include "QDebug"

BoidsWidget::BoidsWidget(QWidget *parent) : QWidget(parent),m_timer(this)
{
     for(int i=0;i<listSize;i++){
         QPoint position(rand()%(parent->width()),rand()%(parent->height()));
         QVector2D velocity(rand()%2,rand()%2);
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
    QVector2D v1,v2,v3;
    for(int i=0;i<boidList.length();i++){
        Boid* b = &boidList[i];
        v1 = cohesion(*b);
        v2 = alignment(*b);
        v3 = separation(*b);

        //qDebug() << "Before " << b->toString();
        //qDebug() << "Cohesion : "<< v1 << " / Alignement : "<<v2 << " / Separation : "<<v3;
        b->velocity = v1 + v2 + v3;
        b->position.setX(b->position.x()+b->velocity.x());
        b->position.setY(b->position.y()+b->velocity.y());

        //Moving the boids to the opposite side if they cross the screen
        if(b->position.x()>this->width()) b->position.setX(0);
        else if(b->position.x()<0) b->position.setX(this->width());

        if(b->position.y()>this->height())b->position.setY(0);
        else if(b->position.y()<0) b->position.setY(this->height());

        //qDebug() << "After " << b->toString();
    }

}

//This rule describes how a boid will try to fly towards the centre of mass of neighbouring boids.
//For now all the boids are taken into account. TODO : only take the neighbours
QVector2D BoidsWidget::cohesion(Boid b){
    QVector2D center;

    //Calculating the centre of mass of all other boids
    for(int i=0;i<boidList.length();i++){
        Boid tempBoid = boidList[i];
        if(&b!=&tempBoid){
            center.setX(center.x()+tempBoid.position.x());
            center.setY(center.y()+tempBoid.position.y());
        }
    }
    center/=(boidList.length()-1);

    //Setting the result to make the boid move towards this centre by a certain %
    center.setX(center.x()-b.position.x());
    center.setY(center.y()-b.position.y());
    return center/cohesionRatio;
}

QVector2D BoidsWidget::alignment(Boid b){

}

QVector2D BoidsWidget::separation(Boid b){

}

BoidsWidget::~BoidsWidget(){
    qDebug() << "Deleting the Boids";
}

