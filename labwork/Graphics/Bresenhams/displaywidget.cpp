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
    image.setPixel(x, y, qRgb(0, 0, 0));
    update();
    updateGeometry();
}

typedef int Sign;

/* Interpolate values between start (x1, y1) and end (x2, y2) */
/* Bresenham's Line Drawing Algorithm */
int DisplayWidget::line(int x1, int y1, int x2, int y2)
{
    int x = x1;
    int y = y1;
    int delx = abs(x2 - x1);
    int dely = abs(y2 - y1);

    Sign s1 = ( (x2-x1) > 0 ) ? ( ( (x2-x1) == 0 ) ? 0 : 1 ) : -1;
    Sign s2 = ( (y2-y1) > 0 ) ? ( ( (y2-y1) == 0 ) ? 0 : 1 ) : -1;

    bool interchange; /* 1 = dydx, 0 = dxdy */

    if( dely > delx )
    {
        int temp = delx;
        delx = dely;
        dely = temp;
        interchange = 1;
    }
    else
        interchange = 0;

    float error = 2 * dely - delx;

    for( int i = 1; i <= delx; i++ )
    {
        drawPixel(x, y);
        emit updateProgressBar((float)i/delx);

        while( error > 0.0 )
        {
            if( interchange )
                x = x + s1;
            else
                y = y + s2;

            error = error - 2 * delx;
        }

        if(interchange)
            y = y + s2;
        else
            x = x + s1;

        error = error + 2 * dely;
    }

    return 0;
}

void DisplayWidget::drawLine()
{
    init();

    if(p1.x() < p2.x())
       line(p1.x(), p1.y(), p2.x(), p2.y());
    else
       line(p2.x(), p2.y(), p1.x(), p1.y());
}
