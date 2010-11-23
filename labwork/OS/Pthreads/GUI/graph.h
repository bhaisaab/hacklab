#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QImage>
#include <QtDebug>
#include <QColor>
#include <QPoint>
#include <QPen>
#include <QPainter>
#include <QProgressBar>
#include <QMouseEvent>

class Graph : public QWidget
{
    Q_OBJECT

public:
    Graph(QWidget *parent = 0);
    void init();
    void drawPixel(int x, int y, int type, int size);
    void drawSpot(int x, int sin, int thr);

protected:
    void paintEvent(QPaintEvent * /* event */);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QImage image;
    QPoint p1, p2;

signals:
    void mousePos(QPoint);
}; //Display Widgetv

#endif // DDADISPLAY_H
