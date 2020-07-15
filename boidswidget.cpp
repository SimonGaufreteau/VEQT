#include "boidswidget.h"
#include "QDebug"

BoidsWidget::BoidsWidget(QWidget *parent) : QWidget(parent)
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

}


QVector2D BoidsWidget::cohesion(){

}

QVector2D BoidsWidget::alignment(){

}

QVector2D BoidsWidget::separation(){

}

