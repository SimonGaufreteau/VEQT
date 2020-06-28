#ifndef MATRIXWIDGET_H
#define MATRIXWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QMap>

class MatrixWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MatrixWidget(QWidget *parent = nullptr);
    ~MatrixWidget();

private:
    static const int time=20;
    static const int baseNumber = 100;
    static const int pixelNb = 2;
    int ttl = 200;
    static const int padding = 100;
    QPainter m_painter;
    QTimer m_timer;
    QColor letterColor;
    QMap<QPointF*,int> charPos;
    void paintEvent(QPaintEvent *event);
    QColor reduceColor(int tempTTL);

private slots :
    void repaintAll();
signals:

};

#endif // MATRIXWIDGET_H
