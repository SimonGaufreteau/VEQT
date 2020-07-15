#include "purplerain.h"
#include <QDebug>
PurpleRain::PurpleRain(QWidget *parent) : QWidget(parent),
    drop_color(194,40,231), bg_color(253,243,255),listRect()

{
    //Drop : (194,40,231)
    //BG : (234,172,249)
    for(int i=0;i<nb_rect;i++){
        int w = rand()%max_w+min_w;
        int h = (int)(w*max_h/max_w);
        QRectF tempRect(rand()%parent->width(),rand()%parent->height(),w,h);
        listRect.append(tempRect);

    }
    m_timer.setInterval(time);
    m_timer.start();
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(repaintDrops()));

}

void PurpleRain::paintEvent(QPaintEvent* e)
{
    //Setting up the painter
    QPainter m_painter(this);

    QPen pen(Qt::PenStyle::NoPen);
    QBrush bg_brush(bg_color);
    m_painter.setPen(pen);
    m_painter.setBrush(drop_color);


    //Drawing the background
    m_painter.fillRect(rect(),bg_brush);

    //Drawing the drops
    for(int i=0;i<nb_rect;i++){
        QRectF* tempRect = &listRect[i];
        float posY = tempRect->y()+tempRect->width()*padding/max_w+min_speed;
        float posX = tempRect->x();
        if(posY>this->height()){
            posX=rand()%this->width();
            posY=-(rand()%top_random);
        }
        tempRect->moveTo(posX,posY);
        m_painter.drawRoundedRect(*tempRect,3,3);
    }
    updateGeometry();
}

void PurpleRain::repaintDrops(){
    repaint();
}


