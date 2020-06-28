#include "matrixwidget.h"
#include <QDebug>

MatrixWidget::MatrixWidget(QWidget *parent) : QWidget(parent),
    m_timer(this),letterColor(38, 153, 19),charPos()
{
    m_timer.setInterval(time);
    m_timer.start();
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(repaintAll()));
    for(int i=0;i<baseNumber;i++){
        //charPos.insert(QPointF(0,0),50);
        charPos.insert(new QPointF(rand()%parent->width(),rand()%(parent->height()+padding)-padding),rand()%ttl);
    }
}

void MatrixWidget::paintEvent(QPaintEvent *event)
{

    QPainter m_painter(this);
    QBrush bg_brush(Qt::GlobalColor::black);

    //Drawing the background
    m_painter.fillRect(rect(),bg_brush);

    m_painter.setPen(letterColor);
    //m_painter.setBackgroundMode(Qt::BGMode::OpaqueMode);
    int beg = 'a';
    int end = 'z';
    QList<QPointF*> keys = charPos.keys();
    for(int i=0;i<keys.length();i++){
        QPointF* tempPos = keys[i];
        tempPos->setY(tempPos->y()+pixelNb);
        m_painter.drawText(*tempPos,QString(char(rand()%(end-beg)+beg)));
        int tempTTL = charPos.value(tempPos);

        //Drawing previous letters (randomly)
        for(int i=0;i<(ttl-tempTTL)*pixelNb/m_painter.fontInfo().pixelSize();i++){
            //QColor tempColor = reduceColor(i);
            //m_painter.setPen(tempColor);
            m_painter.drawText(tempPos->x(),tempPos->y()-(i*m_painter.fontInfo().pixelSize()),QString(char(rand()%(end-beg)+beg)));
        }
        if(tempTTL>0)
            charPos.insert(tempPos,tempTTL-1);

        else{
            charPos.remove(tempPos);
            charPos.insert(new QPointF(rand()%(this->width()),rand()%(this->height()+padding)-padding),ttl);
        }
    }
    updateGeometry();
}

QColor MatrixWidget::reduceColor(int i){
    int red = letterColor.red()-(i/ttl)*letterColor.red();
    int green = letterColor.green()-(i/ttl)*letterColor.green();
    int blue = letterColor.blue()-(i/ttl)*letterColor.blue();
    return QColor(red,green,blue);

    // r-(tempTTL/ttl)*r -> 0 en 50 étapes
}

void MatrixWidget::repaintAll(){
    repaint();
}

MatrixWidget::~MatrixWidget(){
    qDeleteAll(charPos.keys());
}

