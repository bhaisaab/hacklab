#include "graph.h"
#include "math.h"

Graph::Graph(QWidget *parent)
        : QWidget(parent),
        image(1600, 800, QImage::Format_RGB32),
        p1(40, 750), p2(40, 750)
{
    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);

    init();

    setMinimumSize(320, 240);
    resize(1600,800);
}

//-- Paint Event --
void Graph::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), image);
}

void Graph::init()
{
    image.fill(qRgb(255, 255, 255));
    QPainter painter(&image);
    painter.setPen(QPen(QColor(200, 20, 20))); //red
    painter.drawLine(40, 10, 40, 750);
    painter.drawLine(40, 750, 1600, 750);

    painter.setPen(QPen(QColor(0, 0, 0))); //black
    painter.drawText(500, 764, 30, 15, 1, QString("Size"), NULL);
    painter.drawText(4, 350, 35, 15, 1, QString("Time"), NULL);
    setCursor(QCursor(Qt::CrossCursor));
    update();
    updateGeometry();
}

void Graph::mouseMoveEvent(QMouseEvent *event)
{
    int y = 750 - event->pos().y();
    int x = event->pos().x() - 40;
    emit mousePos(QPoint(x, y));
}

// 0  for single
// 1 for thread
void Graph::drawPixel(int x, int y, int type, int size)
{
    QPainter painter(&image);
    QPen pen;

    pen.setWidth(2);

    /* For Thread */
    if(type)
    {
        pen.setColor(QColor(255, 70, 70));
        painter.setPen(pen);
        painter.drawLine(p1.x(), p1.y(), x, y);

        pen.setWidth(4);
        pen.setColor(QColor(50, 50, 50));
        painter.setPen(pen);
        painter.drawPoint(p1.x(), p1.y());


        p1.setX(x);
        p1.setY(y);
    }
    else
    {
        pen.setColor(QColor(70, 70, 255));
        painter.setPen(pen);
        painter.drawLine(p2.x(), p2.y(), x, y);

        pen.setWidth(4);
        pen.setColor(QColor(50, 50, 50));
        painter.setPen(pen);
        painter.drawPoint(p2.x(), p2.y());
        p2.setX(x);
        p2.setY(y);
    }

    pen.setWidth(4);
    pen.setColor(QColor(50, 50, 50));
    painter.setPen(pen);
    painter.drawPoint(x, y);

    pen.setColor(QColor(30, 30, 30));
    painter.setPen(pen);

    QString t;
    t.setNum(size);
    painter.drawPoint(x, 750);
    painter.drawText(x, 750, 30, 15, 1, t, NULL);

    update();
    updateGeometry();
}

void Graph::drawSpot(int x, int sin, int thr)
{
    QPainter painter(&image);
    QPen pen;

    pen.setWidth(5);
    pen.setColor(QColor(50, 255, 50));
    painter.setPen(pen);
    painter.drawPoint(x, sin);

    pen.setColor(QColor(50, 255, 50));
    painter.setPen(pen);
    painter.drawPoint(x, thr);

    painter.drawPoint(x, 750);
    update();
    updateGeometry();
}
