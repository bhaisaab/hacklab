#include "displaywidget.h"
#include "math.h"

DisplayWidget::DisplayWidget(QWidget *parent)
        : QWidget(parent),
        image(1200, 800, QImage::Format_RGB32),
        p1(0, 0),
        p2(0, 0)
{
    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
    image.fill(qRgb(255, 255, 255));

    init();
    flag = false;
    redraw = true;
    setMinimumSize(320, 240);
    resize(1200,800);

}

//-- Paint Event --
void DisplayWidget::paintEvent(QPaintEvent * /* event */)

{
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), image);
}

void DisplayWidget::init()
{
    if(redraw)
        image.fill(qRgb(255, 255, 255));
    QPainter painter(&image);
    painter.setPen(QPen(QColor(255, 0, 0)));
    painter.drawLine(600, 0, 600, 800);
    painter.drawLine(0, 400, 1280, 400);
    setCursor(QCursor(Qt::CrossCursor));
            painter.setPen(QPen(QColor(190, 190, 190)));
            painter.drawLine(p1.x(), 0, p1.x(), 800);
            painter.drawLine(0, p1.y(), 1280, p1.y());

            painter.setPen(QPen(QColor(190, 190, 190)));
            painter.drawLine(p2.x(), 0, p2.x(), 800);
            painter.drawLine(0, p2.y(), 1280, p2.y());
}

void DisplayWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(!flag)
        {   p1 = event->pos(); drawPixel(p1.x(), p1.y()); flag = true;
            QPainter painter(&image);
            painter.setPen(QPen(QColor(0, 255, 0)));
            painter.drawLine(p1.x(), 0, p1.x(), 800);
            painter.drawLine(0, p1.y(), 1280, p1.y());

        }
        else
        {   p2 = event->pos(); drawPixel(p2.x(), p2.y()); flag = false;
                    QPainter painter(&image);
            painter.setPen(QPen(QColor(0, 255, 0)));
            painter.drawLine(p2.x(), 0, p2.x(), 800);
            painter.drawLine(0, p2.y(), 1280, p2.y());

        }
    }
}

void DisplayWidget::mouseMoveEvent(QMouseEvent *event)
{
    int y = 400 - event->pos().y();
    int x = event->pos().x() - 600;
    emit mousePos(QPoint(x, y));
}

void DisplayWidget::drawPixel(int x, int y)
{
    usleep(10000);
    int rx = (p1.x() + p2.x()) / 2 ;
    int ry = (p2.y() + p1.y()) / 2;

    image.setPixel(x+rx, y+ry, qRgb(0, 0, 0));
    image.setPixel(-x+rx, y+ry, qRgb(0, 0, 0));
    image.setPixel(x+rx, -y+ry, qRgb(0, 0, 0));
    image.setPixel(-x+rx, -y+ry, qRgb(0, 0, 0));
    update();
    updateGeometry();
}

typedef int Sign;

/* Interpolate values between start (x1, y1) and end (x2, y2) */
/* Bresenham's Ellipse Drawing Algorithm */
int DisplayWidget::ellipse(int x, int y, int a, int b)
{
    x = (int)(a+1/2);
    y = 0;

    int taa = a*a;
    int t2aa = 2 * taa;
    int t4aa = 2 * t2aa;

    int tbb = b * b;
    int t2bb = 2 * tbb;
    int t4bb = 2 * t2bb;

    int t2abb = t2bb * x;

    int t2bbx = t2bb * x;
    int tx = x;

    int d1 = t2bbx * (x-1) + tbb/2 + t2aa * (1-tbb);

    while((t2bb*tx) > (t2aa * y))
    {
        drawPixel(x,y);

        if(d1 < 0)
        {
            y++;
            d1 = d1 + t4aa*y + t2aa;
            tx = x-1;
        }
        else
        {
            x--;
            y++;
            d1 = d1 - t4bb * x + t4aa * y + t2aa;
            tx = x;
        }
    }

    int d2 = t2bb * (x*x+1) - t4bb*x + t2aa * (y*y + y - tbb) + taa/2;

    while(x>=0)
    {
        drawPixel(x,y);
        if(d2<0)
        {
            x--;
            y++;
            d2 = d2 + t4aa * y - t4bb*x + t2bb;
        }
        else
        {
            x--;
            d2 = d2 - t4bb * x + t2bb;
        }

    }

    return 0;
}

void DisplayWidget::drawLine()
{
    init();

    ellipse((p2.x()+p1.x())/2, (p2.y()+p1.y())/2, abs(p2.x()-p1.x()) / 2, abs(p2.y()-p1.y()) / 2 );

}
