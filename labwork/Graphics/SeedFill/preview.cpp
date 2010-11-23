
#include <QtGui>
#include <QtDebug>
#include "preview.h"

//! [0]
Preview::Preview(QWidget *parent)
    : QFrame(parent),
image(200, 150, QImage::Format_RGB32)
{
    setAttribute(Qt::WA_StaticContents);
    image.fill(qRgb(255, 255, 255));
    resize(200, 150);

}


void Preview::updatePreview(QImage newImage)
{
    int newWidth = 200, newHeight = 150;

    QImage updateImage = newImage.scaled(200, 150, Qt:: KeepAspectRatio, Qt::SmoothTransformation);
    image = updateImage.convertToFormat(QImage::Format_RGB32);
    newWidth = image.width();
    newHeight =image.height();
    //qDebug() <<"Preview:: "<<"x: "<<image.width()<<"y: "<<image.height();

    resize(newWidth, newHeight);
    update();
    emit updatePreviewScrollArea();
}


void Preview::clearImage()

{
    image.fill(qRgb(255, 255, 255));
    update();
}



void Preview::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), image);
}
