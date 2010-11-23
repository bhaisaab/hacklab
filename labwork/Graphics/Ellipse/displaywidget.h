#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include <QImage>
#include <QColor>
#include <QPoint>
#include <QPen>
#include <QPainter>
#include <QProgressBar>
#include <QMouseEvent>

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    DisplayWidget(QWidget *parent = 0);
    int ellipse(int x, int y, int a, int b);
    void init();
    void drawPixel(int x, int y);
    void drawLine();
    bool redraw;


protected:
    void paintEvent(QPaintEvent * /* event */);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QImage image;
    QPoint p1;
    QPoint p2;
    bool flag;

signals:
    void updateProgressBar(float);
    void mousePos(QPoint);
}; //Display Widgetv

#endif // DISPLAYWIDGET_H
