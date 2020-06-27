#ifndef PURPLERAIN_H
#define PURPLERAIN_H

#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QTimer>

class PurpleRain : public QWidget
{
    Q_OBJECT
public:
    explicit PurpleRain(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

private:
    static const int nb_rect=200;
    static const int time=5;
    static const int padding=2;
    static const int top_random=500;
    static const int min_speed=1;
    static const int min_w = 2;
    static const int max_w = 4;
    static const int min_h = 20;
    static const int max_h = 40;
    QPainter m_painter;
    QColor drop_color;
    QColor bg_color;
    QVector<QRectF> listRect;
    QTimer m_timer;

private slots:
    void repaintDrops();

signals:

};

#endif // PURPLERAIN_H
