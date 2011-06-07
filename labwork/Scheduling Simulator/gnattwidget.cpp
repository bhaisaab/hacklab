#include "gnattwidget.h"

#define HEIGHT 70

#define AXIS_HEIGHT (HEIGHT - 30)
#define TIME 60
#define STEP 5
#define STEP_SIZE 21
#define STEP_HEIGHT 6

#define WIDTH (TIME * STEP_SIZE)

#define X_OFF 25
#define Y_OFFSET 0

GnattWidget::GnattWidget(QWidget *parent) :
        QWidget(parent),
        image(WIDTH, HEIGHT, QImage::Format_RGB32)
{
    setFixedSize(WIDTH, HEIGHT);
    setAttribute(Qt::WA_StaticContents);
    setMinimumSize(WIDTH, HEIGHT);
    resize(WIDTH, HEIGHT);
    this->setGeometry(0, 0, WIDTH, HEIGHT);

    init();
}

void GnattWidget::init()
{
    image.fill(qRgb(255, 255, 255)); //white

    QPainter painter(&image);
    painter.setPen(QPen(QColor(180, 180, 180))); //gray


    QString time;

    //x-axis
    painter.drawLine(0 + X_OFF, AXIS_HEIGHT, WIDTH + X_OFF, AXIS_HEIGHT);
    //y-axis
    painter.drawLine(0 + X_OFF, 0, 0 + X_OFF, AXIS_HEIGHT);

    painter.drawText(4, HEIGHT/2, "P" + time.setNum(pid));

    painter.setPen(QPen(QColor(80, 80, 80))); //darker gray

    for ( int i = 0; i < TIME+1; i++ )
    {
        painter.drawLine( X_OFF + i*(STEP_SIZE-1), AXIS_HEIGHT, X_OFF + i*(STEP_SIZE-1), AXIS_HEIGHT + STEP_HEIGHT);
        QFont newFont = font();
        newFont.setPointSize(7);
        setFont(newFont);

        if( (i% STEP)==0 )
        {
            QFontMetrics metrics(font());
            int w = metrics.width(time.setNum(i));
            painter.drawLine(X_OFF + i*(STEP_SIZE-1), AXIS_HEIGHT, X_OFF + i*(STEP_SIZE-1), AXIS_HEIGHT + STEP_HEIGHT + 5);

            painter.drawText(X_OFF + i*(STEP_SIZE-1)-w/2, AXIS_HEIGHT+STEP_HEIGHT+20, time);
        }
    }
    update();
    updateGeometry();
}

void GnattWidget::paintEvent(QPaintEvent *)
{    
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), image);

    //QWidget::paintEvent(event);
}

void GnattWidget::drawTask(int time, int size)
{
    QPainter painter(&image);

    painter.setBrush(color);
    painter.setPen(QColor(140,140,140));
    painter.drawRect(X_OFF + time * (STEP_SIZE-1), 18, size * (STEP_SIZE-1), AXIS_HEIGHT-18-1);

}

void GnattWidget::setColor(QColor col)
{
    color = col;
}

void GnattWidget::setPeriod(int interval)
{
    period = interval;
    init();

    QPainter painter(&image);
    painter.setPen(QColor(100,100,100));

    for ( int i = 0; i < TIME+1; i++ )
    {
        if( (i%period) == 0 )
        {
            painter.drawLine(X_OFF + i*(STEP_SIZE-1), AXIS_HEIGHT, X_OFF + i*(STEP_SIZE-1), 6);
        }
    }
}

void GnattWidget::setPid(int id)
{
    pid = id;
}
