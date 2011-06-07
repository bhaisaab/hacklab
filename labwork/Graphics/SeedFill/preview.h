

#ifndef PREVIEW_H
#define PREVIEW_H
#include <QtDebug>
#include <QColor>
#include <QImage>
#include <QFrame>
#include <QWidget>


//! [0]
class Preview : public QFrame
{
    Q_OBJECT

public:
    Preview(QWidget *parent = 0);
    void updatePreview(QImage newImage);

signals:
   void updatePreviewScrollArea();

public slots:
    void clearImage();


protected:
    void paintEvent(QPaintEvent *event);

    //void resizeEvent(QResizeEvent *event);

private:
    //void resizeImage(QImage *image, const QSize &newSize);


    QImage image;
};
//! [0]

#endif
