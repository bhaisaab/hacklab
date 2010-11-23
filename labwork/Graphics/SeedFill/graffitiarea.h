

#ifndef GRAFFITIAREA_H
#define GRAFFITIAREA_H
#include <QtDebug>
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QtGui>
# define MAXSIZE 480000

 struct PixelStack{
        int top;
        QPoint items[MAXSIZE];
    };


//! [0]
class GraffitiArea : public QWidget
{
    Q_OBJECT

public:
    GraffitiArea(QWidget *parent = 0);

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    void setEraserWidth(int newWidth);
    void setFillColor(const QColor &newColor);
    void stackPush(QPoint x, PixelStack *ps);
    QPoint stackPop(PixelStack *ps);
    //void insertShape(QString text);

    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }
    int eraserWidth() const { return myEraserWidth; }
    QColor fillColor() const { return myPenColor; }
    QImage graffitiImage() const { return image; }



    void deSelectAll();

signals:
   void colorSelected();
   void updatePreview();

public slots:
    void clearImage();
    void print();
    void pencilPressEvent();
    void linePressEvent();
    void eraserPressEvent();
    void rectanglePressEvent();
    void ellipsePressEvent();
    void fillPressEvent();
    void textPressEvent();
    void colorSelPressEvent();
    void imagePressEvent();
protected:
    //void pencilPressEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    //void resizeEvent(QResizeEvent *event);
    void setImage(const QImage &loadedImage);


private:
    struct queue{
            int front;
           QPoint pointQueue[1000000];
            int rear;
       }fillPoints;

    void addToQueue(int X, int Y);
    void deQueue();
    void eraseTo(const QPoint &endPoint);
    void drawLineTo(const QPoint &endPoint);
    void drawPoint();
    void drawRectangle(const QPoint &endPoint);
    void drawEllipse(const QPoint &endPoint);
    void seedFill(int x, int y, QRgb targetColor, QColor replacementColor);//, bool fillLeft, bool fillRight, bool fillUp, bool fillDown);
         QColor selectedColor(const QPoint &selectedPoint);
    //void resizeImage(QImage *image, const QSize &newSize);
    void drawInsertedImage(QPoint start, QPoint end);

    void setupPainter(QPainter &painter);

    int myPenWidth;
    //int myLineWidth;
    //int myDrawWidth;
    int myEraserWidth;
    QColor myPenColor;
    QColor myFillColor;
    QImage image;
    QImage insertedImage;
    QPoint lastPoint;
    QPoint startingPoint;
    QPoint endingPoint;
    bool pencil;
    bool eraser;
    bool line;
    bool rectangle;
    bool ellipse;
    bool fill;
    bool text;
    bool colorSelection;
    bool insertImage;
    bool modified;
    bool scribbling;
    bool lining;
    bool erasing;
    bool filling;
    QString paintText;
    QLabel *labelPosition;
    QPainterPath pendingPath;
    int i;
    int j;

};
//! [0]

#endif
