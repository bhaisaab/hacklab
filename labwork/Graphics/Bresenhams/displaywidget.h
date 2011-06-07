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
    int line(int x1, int y1, int x2, int y2);
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
