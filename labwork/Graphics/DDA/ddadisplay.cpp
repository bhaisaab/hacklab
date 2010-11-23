#include "ddadisplay.h"
#include "math.h"

DDADisplay::DDADisplay(QWidget *parent)
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
void DDADisplay::paintEvent(QPaintEvent * /* event */)

{
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), image);
}

void DDADisplay::init()
{
    if(redraw)
        image.fill(qRgb(255, 255, 255));
    QPainter painter(&image);
    painter.setPen(QPen(QColor(255, 0, 0)));
    painter.drawLine(600, 0, 600, 800);
    painter.drawLine(0, 400, 1280, 400);
    setCursor(QCursor(Qt::CrossCursor));
    qDebug() << p1 << p2;
}

void DDADisplay::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(!flag)
        {   p1 = event->pos(); drawPixel(p1.x(), p1.y()); flag = true; }
        else
        {   p2 = event->pos(); drawPixel(p2.x(), p2.y()); flag = false; }
    }
    qDebug() << p1 << p2;
}

void DDADisplay::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << event->pos();
    int y = 400 - event->pos().y();
    int x = event->pos().x() - 600;
    emit mousePos(QPoint(x, y));
}

void DDADisplay::drawPixel(int x, int y)
{
    image.setPixel(x, y, qRgb(0, 0, 0));
    update();
    updateGeometry();
}

/* Interpolate values between start (x1, y1) and end (x2, y2) */
int DDADisplay::DDA(int x1, int y1, int x2, int y2)
{
    float y = y1;
    int delx = x2 - x1;
    int dely = y2 - y1;

    float dydx = (float) dely / (float) delx;

    int lim1 = x1;
    int lim2 = x2;
    bool flag = true;

    if(delx < dely)
    {
        lim1 = y1;
        lim2 = y2;
        dydx = (float) delx / (float) dely;
        flag = false;
        y = x1;
    }
    else
    {
        lim1 = x1;
        lim2 = x2;
        dydx = (float) dely / (float) delx;
        flag = true;
        y = y1;
    }

    for(int x = lim1; x <= lim2; x++){
        if(flag)
            drawPixel(x, round(y));
        else
            drawPixel(round(y), x);

        y += dydx;
      //  emit updateProgressBar((float)(x-x1)/delx);
    }
    return dydx;
}

void DDADisplay::doDDA()
{
    init();

    int delx = p1.x() - p2.x();
    int dely = p1.y() < p2.y();

    if(delx < 0)
        delx *= -1;
    if(dely < 0)
        dely *= -1;

    if(delx > dely)
    {
       if(p1.x() < p2.x())
            DDA(p1.x(), p1.y(), p2.x(), p2.y());
       else
            DDA(p2.x(), p2.y(), p1.x(), p1.y());
    }
    else
    {
       if(p1.y() < p2.y())
            DDA(p1.x(), p1.y(), p2.x(), p2.y());
       else
            DDA(p2.x(), p2.y(), p1.x(), p1.y());

    }


}
