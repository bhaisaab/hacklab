#include "graph.h"
#include "math.h"

Graph::Graph(QWidget *parent)
        : QWidget(parent),
        image(1600, 600, QImage::Format_RGB32),
        p1(40, 500), p2(40, 500), p3(40, 500)
{
    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);

    init();

    setMinimumSize(320, 240);
    resize(1600,600);
}

//-- Paint Event --
void Graph::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawImage(QPoint(0, 0), image);
}

void Graph::init()
{
    image.fill(qRgb(50, 60, 50));
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor(200, 200, 200))); //off-white
    painter.drawLine(40, 10, 40, 500);
    painter.drawLine(40, 500, 1600, 500);

    painter.setPen(QPen(QColor(70, 255, 70)));
    painter.drawText(60, 10, 50, 15, 1, QString("Single"), NULL);
    painter.setPen(QPen(QColor(70, 70, 255)));
    painter.drawText(60, 30, 90, 15, 1, QString("PThreads"), NULL);
    painter.setPen(QPen(QColor(255, 70, 70)));
    painter.drawText(60, 50, 50, 15, 1, QString("Java"), NULL);

    painter.setPen(QPen(QColor(255, 255, 255))); //white
    painter.drawText(300, 525, 200, 15, 1, QString("Numbers of Fibonacci Nos. (n)"), NULL);
    painter.drawText(4, 350, 35, 15, 1, QString("Time"), NULL);
    setCursor(QCursor(Qt::CrossCursor));
    update();
    updateGeometry();
}

void Graph::mouseMoveEvent(QMouseEvent *event)
{
    int y = 500 - event->pos().y();
    int x = event->pos().x() - 40;
    emit mousePos(QPoint(x, y));
}

// 0  for single
// 1 for thread
void Graph::drawPixel(int x, int y, int type, int size)
{
    QPainter painter(&image);
    QPen pen;
    painter.setRenderHint(QPainter::Antialiasing, true);
    pen.setWidth(2);

    /* 1 For Thread */
    if(type == 1)
    {
        pen.setColor(QColor(70, 70, 255));
        painter.setPen(pen);
        painter.drawLine(p1.x(), p1.y(), x, y);

        pen.setWidth(5);
        pen.setCapStyle(Qt::RoundCap);
        pen.setColor(QColor(255, 255, 255));
        painter.setPen(pen);
        painter.drawPoint(p1.x(), p1.y());


        p1.setX(x);
        p1.setY(y);
    }
    else
    if(type == 2)
    {
        pen.setColor(QColor(255, 70, 70));
        painter.setPen(pen);
        painter.drawLine(p3.x(), p3.y(), x, y);

        pen.setWidth(5);
        pen.setCapStyle(Qt::RoundCap);
        pen.setColor(QColor(255, 255, 255));
        painter.setPen(pen);
        painter.drawPoint(p3.x(), p3.y());
        p3.setX(x);
        p3.setY(y);
    }
    else
    {
        pen.setColor(QColor(70, 255, 70));
        painter.setPen(pen);
        painter.drawLine(p2.x(), p2.y(), x, y);

        pen.setWidth(5);
        pen.setCapStyle(Qt::RoundCap);
        pen.setColor(QColor(255, 255, 255));
        painter.setPen(pen);
        painter.drawPoint(p2.x(), p2.y());
        p2.setX(x);
        p2.setY(y);
    }

    pen.setWidth(2);
    pen.setColor(QColor(220, 220, 220));
    painter.setPen(pen);
    painter.drawPoint(x, y);

    pen.setColor(QColor(230, 230, 230));
    painter.setPen(pen);

    QString t;
    t.setNum(size);
    painter.drawPoint(x, 500);
    painter.drawText(x, 500, 30, 15, 1, t, NULL);

    update();
    updateGeometry();
}

void Graph::drawSpot(int x, int sin, int thr)
{
    QPainter painter(&image);
    QPen pen;
    painter.setRenderHint(QPainter::Antialiasing, true);
    pen.setWidth(8);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(QColor(130, 200, 105));
    painter.setPen(pen);
    painter.drawPoint(x, sin);
    painter.drawPoint(x, thr);
    painter.drawPoint(x, 500);
    update();
    updateGeometry();
}
