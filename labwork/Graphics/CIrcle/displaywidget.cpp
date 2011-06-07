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

                painter.setPen(QPen(QColor(200, 200, 200)));
            painter.drawLine(p1.x(), 0, p1.x(), 800);
            painter.drawLine(0, p1.y(), 1280, p1.y());

            painter.setPen(QPen(QColor(200, 200, 200)));
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
            painter.drawLine(0, p2.y(), 1280, p2.y());}
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
/* Bresenham's Circle Drawing Algorithm */
int DisplayWidget::circle(int x, int y, int R)
{
    int xi = 0;
    int yi = R;
    int deli = 2 * (1-R);
    int Limit = 0;
    int delta, deldash;

    while(yi >= Limit)
    {
        drawPixel(xi, yi);
        if(deli < 0)
        {
            delta = 2 * deli + 2 * yi - 1;
            if(delta <= 0)
            {
                xi++;
                deli = deli + 2*xi + 1;
            }
            else
            {
                xi++;
                yi--;
                deli = deli + 2 * xi - 2 * yi + 2;
            }
        }
        else
            if(deli > 0)
            {
                deldash = 2 * deli - 2 * xi - 1;
                if(deldash < 0)
                {
                    xi++;
                    yi--;
                    deli = deli + 2 * xi - 2 * yi + 2;
                }
                else
                {
                    yi--;
                    deli = deli - 2*yi + 1;
                }
            }
            else
                if(deli == 0)
                {
                    xi++;
                    yi--;
                    deli = deli + 2 * xi - 2 * yi + 2;
                }
    }
    return 0;
}

void DisplayWidget::drawLine()
{
    init();

    circle((p2.x()+p1.x())/2, (p2.y()+p1.y())/2, sqrt(pow(p2.x()-p1.x(), 2) + pow(p2.y()-p1.y(), 2)) / 2);

}
