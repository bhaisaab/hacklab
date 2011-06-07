#ifndef DDADISPLAY_H
#define DDADISPLAY_H

#include <QWidget>
#include <QImage>
#include <QtDebug>
#include <QColor>
#include <QPoint>
#include <QPen>
#include <QPainter>
#include <QProgressBar>
#include <QMouseEvent>

class DDADisplay : public QWidget
{
    Q_OBJECT

public:
    DDADisplay(QWidget *parent = 0);
    int DDA(int x1, int y1, int x2, int y2);
    void init();
    void drawPixel(int x, int y);
    void doDDA();
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

#endif // DDADISPLAY_H
