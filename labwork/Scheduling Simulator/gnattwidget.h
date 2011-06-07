#ifndef GNATTWIDGET_H
#define GNATTWIDGET_H

#include <QWidget>
#include <QImage>
#include <QColor>
#include <QPoint>
#include <QPen>
#include <QPainter>

class GnattWidget : public QWidget
{
    Q_OBJECT
public:
    GnattWidget(QWidget *parent = 0);
    void init();
    void drawTask(int time, int size);
    void setColor(QColor col);
    void setPeriod(int interval);
    void setPid(int id);

protected:
    void paintEvent(QPaintEvent *);

private:
    QImage image;
    QColor color;
    int period;
    int pid;
};

#endif // GNATTWIDGET_H
