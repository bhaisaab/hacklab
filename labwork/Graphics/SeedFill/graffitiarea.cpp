
#include <QtGui>
#include <QtDebug>
#include "graffitiarea.h"



//! [0]
GraffitiArea::GraffitiArea(QWidget *parent):
    QWidget(parent),
    image(800, 600, QImage::Format_RGB32),
    lastPoint(-1, -1)
{
    setAttribute(Qt::WA_StaticContents);
    //setAttribute(Qt::WA_NoBackground);
    deSelectAll();
    myPenWidth = 1;
    myPenColor = Qt::black;
    myFillColor = Qt::black;
    myEraserWidth = 20;
    labelPosition = new QLabel("Position", this );
    labelPosition->setVisible(false);
    labelPosition->setPalette(QColor(0,0,0));
    labelPosition->setBackgroundRole(QPalette::Dark);
    labelPosition->setAutoFillBackground(false);
    i = labelPosition->width();
    j = labelPosition->height();
    image.fill(qRgb(255, 255, 255));
    setMinimumSize(400, 300);
    resize(800,600);
    
}


void GraffitiArea::stackPush(QPoint x, PixelStack *ps)
    {
        if(ps->top == MAXSIZE-1){
            qDebug()<<"Error: stack overflow";
            exit(EXIT_FAILURE);
        } else
            ps->items[++(ps->top)] = x;

        return;
    }

QPoint GraffitiArea::stackPop(PixelStack *ps)
    {
        if(ps->top <= 0){
            printf("Error: stack underflow");
            exit(EXIT_FAILURE);
        } else
            return(ps->items[(ps->top)--]);
    }


bool GraffitiArea::openImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    setImage(loadedImage);
    emit updatePreview();
    return true;
}



bool GraffitiArea::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;
    //resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}



void GraffitiArea::setImage(const QImage &loadedImage)
{
    image = loadedImage.convertToFormat(QImage::Format_RGB32);
    resize(loadedImage.size());
    update();
    updateGeometry();
}



void GraffitiArea::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}



void GraffitiArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}



void GraffitiArea::setEraserWidth(int newWidth)
{
    myEraserWidth = newWidth;
}



void GraffitiArea::setFillColor(const QColor &newColor)
{
    myFillColor = newColor;
}



void GraffitiArea::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
    emit updatePreview();
}



//-- MousePress Event --
void GraffitiArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && pencil) {
        lastPoint = event->pos();
        labelPosition->setGeometry(lastPoint.x(), lastPoint.y(), i, j);
        labelPosition->setVisible(true);
        qDebug() <<"Scribble:: "<<"x: "<<lastPoint.x()<<"y: "<<lastPoint.y()<<"PencilWidth: "<<myPenWidth<<"PencilColour: "<<myPenColor;
        //printf("%d, %d", lastPoint.x(), lastPoint.y());
        scribbling = true;
    }
    else if(event->button() == Qt::LeftButton && line){
        lastPoint = event->pos();
        startingPoint = lastPoint;
        drawPoint();
        //qDebug() <<"Line:: "<<"x: "<<lastPoint.x()<<"y: "<<lastPoint.y();
        //lining = true;
    }
    else if(event->button() == Qt::LeftButton && eraser){
        lastPoint = event->pos();
        qDebug() <<"Eraser:: "<<"x: "<<lastPoint.x()<<"y: "<<lastPoint.y()<<"EraserWidth: "<<myEraserWidth;
        erasing = true;
    }
    else if(event->button() == Qt::LeftButton && rectangle){
        lastPoint = event->pos();
        startingPoint = lastPoint;
        drawPoint();
    }
    else if(event->button() == Qt::LeftButton && ellipse){
        lastPoint = event->pos();
    }
    else if(event->button() == Qt::LeftButton && fill){
        lastPoint = event->pos();
    }
    else if(event->button() == Qt::LeftButton && text){
            QPainter painter(&image);
            //setupPainter(painter);
            //const QRectF boundingRect = pendingPath.boundingRect();
            painter.drawText(event->pos(), paintText);
            update();
            text = false;
            setCursor(Qt::ArrowCursor);
    }
    else if(event->button() == Qt::LeftButton && insertImage){
            lastPoint = event->pos();
    }
    else if(event->button() == Qt::LeftButton && colorSelection){
        QPoint curPoint = event->pos();
        myPenColor = selectedColor(curPoint);
        emit colorSelected();
    }
}



//-- MouseMove Event --
void GraffitiArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
    {
        QPoint lastPoint1 = event->pos();
        drawLineTo(event->pos());
        labelPosition->setGeometry(lastPoint1.x(), lastPoint1.y(), i, j);
        qDebug() <<"Scribble:: "<<"x: "<<lastPoint1.x()<<"y: "<<lastPoint1.y()<<"PencilWidth: "<<myPenWidth<<"PencilColour: "<<myPenColor;
    }
    else if ((event->buttons() & Qt::LeftButton) && erasing){
        eraseTo(event->pos());
        QPoint lastPoint1 = event->pos();
        qDebug() <<"Eraser:: "<<"x: "<<lastPoint1.x()<<"y: "<<lastPoint1.y()<<"EraserWidth: "<<myEraserWidth;
    }
    //emit updatePreview();
}



//-- MouseRelease Event --
void GraffitiArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos());
        labelPosition->setVisible(false);
        scribbling = false;
    }
    else if(event->button() == Qt::LeftButton && line){
        drawLineTo(event->pos());
        endingPoint = event->pos();
        qDebug() <<"Line:: "<<"x1: "<<startingPoint.x()<<"y1: "<<startingPoint.y()<<"x2: "<<endingPoint.x()<<"y2: "<<endingPoint.y();
        //lining = false;
    }
    else if(event->button() == Qt::LeftButton && erasing){
        eraseTo(event->pos());
        erasing = false;
    }
    else if(event->button() == Qt::LeftButton && rectangle){
        drawRectangle(event->pos());
        endingPoint = event->pos();
        qDebug() <<"Rectangle:: "<<"x: "<<startingPoint.x()<<"y: "<<startingPoint.y()<<"Width: "<<endingPoint.x() - startingPoint.x()<<"Height: "<<endingPoint.y() - startingPoint.y();
    }
    else if(event->button() == Qt::LeftButton && ellipse){
        drawEllipse(event->pos());
    }
    
    else if(event->button() == Qt::LeftButton && fill){
        //lastPoint = event->pos();
        seedFill(lastPoint.x(), lastPoint.y(), image.pixel(lastPoint.x(), lastPoint.y()), myPenColor);//, true, true, true, true);
        update();
    }
    else if(event->button() == Qt::LeftButton && insertImage){
        //lastPoint = event->pos();
        drawInsertedImage(lastPoint, event->pos());
        update();
        insertImage = false;
        setCursor(Qt::ArrowCursor);
    }
    emit updatePreview();
}


//-- Paint Event --
void GraffitiArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), image);
}



//-- PencilPress Event --
void GraffitiArea::pencilPressEvent()
{

    deSelectAll();
    pencil = true;

    QCursor cursor(QPixmap(":/tools/images/tools/pencil.png"),5,26);
    setCursor(cursor);
}



//-- LinePress Event --
void GraffitiArea::linePressEvent()
{
    deSelectAll();
    line = true;
}




//-- EraserPress Event --
void GraffitiArea::eraserPressEvent()
{
    deSelectAll();
    eraser = true;
    QCursor cursor(QPixmap(":/tools/images/tools/eraser.png"),12,24);
    setCursor(cursor);
}



//-- RectanglePress Event --
void GraffitiArea::rectanglePressEvent()
{
    deSelectAll();
    rectangle = true;
    //QMessageBox::about(parent, tr("About Graffiti"));
    QCursor cursor(QPixmap(":/tools/images/tools/rectangle.png"),5,26);
    setCursor(Qt::CrossCursor);
}




//-- EllipsePress Event --
void GraffitiArea::ellipsePressEvent()
{
    deSelectAll();
    ellipse = true;
    //QMessageBox::about(parent, tr("About Graffiti"));
       QCursor cursor(QPixmap(":/tools/images/tools/ellipse.png"),5,26);
    setCursor(Qt::CrossCursor);
}



//-- FillPress Event --
void GraffitiArea::fillPressEvent()
{
    deSelectAll();
    fill = true;
    //QMessageBox::about(parent, tr("About Graffiti"));
       QCursor cursor(QPixmap(":/tools/images/tools/fill.png"),25,24);
    setCursor(cursor);
}



//-- TextPress Event --
void GraffitiArea::textPressEvent()
{
    deSelectAll();
    text = true;
    paintText = QInputDialog::getText(this, tr("Graffiti"), tr("Give Text"));
    //QMessageBox::about(parent, tr("About Graffiti"));
      // QCursor cursor(QPixmap(":/tools/images/tools/fill.png"),5,26);
    setCursor(Qt::CrossCursor);
}

//-- Color Selection Press Event --
void GraffitiArea::colorSelPressEvent()
{
    deSelectAll();
    colorSelection = true;
    setCursor(Qt::CrossCursor);
}

//-- ImagePress Event --
void GraffitiArea::imagePressEvent()
{

    deSelectAll();
    insertImage = true;
    QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty()){
            if (!insertedImage.load(fileName))
            qDebug() <<"No Image";
        }
    setCursor(Qt::CrossCursor);
}

//-- DrawLineTo Function:: To draw Line from one point to other --
void GraffitiArea::drawLineTo(const QPoint &endPoint)
{   
    /*if (pencil == true)
    myDrawWidth = myPenWidth;
    else if (line == true)
    myDrawWidth = myLineWidth;*/
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}



//-- EraseTo Function:: To erase --
void GraffitiArea::eraseTo(const QPoint &endPoint)
{   
    QPainter painter(&image);
    painter.setPen(QPen(Qt::white, myEraserWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myEraserWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

//-- Draw Image --
void GraffitiArea::drawInsertedImage(QPoint start, QPoint end)
{
    int width = end.x() - start.x();
    int height = end.y() - start.y();
    if (width < 0){
        start.setX(end.x());
        width = 0 - width;
    }
    QPainter painter(&image);
    insertedImage = insertedImage.scaled(width, height, Qt:: IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawImage(start, insertedImage);
    update();
}

//-- DrawLineTo Function:: To draw Line from one point to other --
void GraffitiArea::drawPoint()
{
    /*if (pencil == true)
    myDrawWidth = myPenWidth;
    else if (line == true || rectangle == true || ellipse == true)
    myDrawWidth = myLineWidth;*/
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawPoint(lastPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, lastPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    //lastPoint = currentPoint;
}




void GraffitiArea::drawRectangle(const QPoint &endPoint)
{
    int width = endPoint.x() - lastPoint.x();
    int height = endPoint.y() - lastPoint.y();
    //myDrawWidth = myLineWidth;
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawRect(lastPoint.x(), lastPoint.y(), width, height);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}




void GraffitiArea::drawEllipse(const QPoint &endPoint)
{
    //if (pencil == true)
    //myDrawWidth = myPenWidth;
    //else if (line == true)
    int width = endPoint.x() - lastPoint.x();
    int height = endPoint.y() - lastPoint.y();
    //myDrawWidth = myLineWidth;
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawEllipse(lastPoint.x(), lastPoint.y(), width, height);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}



void GraffitiArea::seedFill(int x, int y, QRgb targetColor, QColor replacementColor )
{
    int m, n;
    QPoint temp = QPoint(x,y);
    QStack<QPoint> drawArea;
    QRgb color = replacementColor.rgb();
    QColor nodeColor = image.pixel(x, y);
    drawArea.push(temp);
    while(drawArea.size() > 0)
    {
        temp = drawArea.pop();
        image.setPixel(temp, color);
        m = temp.x();
        n = temp.y();
         if(m > 0 && image.pixel(m-1,n) == targetColor)
             drawArea.push(QPoint(m-1,n));
         if(m < image.width()-1 && image.pixel(m+1,n) == targetColor)
             drawArea.push(QPoint(m+1,n));
         if(n > 0 && image.pixel(m,n-1) == targetColor)
             drawArea.push(QPoint(m,n-1));
         if(n < image.height()-1 && image.pixel(m,n+1) == targetColor)
             drawArea.push(QPoint(m,n+1));
    }
}



QColor GraffitiArea::selectedColor(const QPoint &selectedPoint)
{
    qDebug() <<"Color:: "<<image.pixel(selectedPoint);
    QColor newColor = image.pixel(selectedPoint);
    if(newColor.isValid())
    return newColor;
    else
    return myPenColor;
}



/*void addToQueue(int X, int Y)
{
    if(fillPoints.rear < 1000000)
    {
        if(fillPoint.front == -1)
            front++;
    fillPoint.rear++;
    fillPoints.pointQueue[rear].setX(X);
    fillPoints.pointQueue[rear].setY(Y);
     }
}


void deQueue()
{
    if(fillPoint.front  != fillPoint. rear)
    fillPoint.front++;
    else
    fillPoint.front = fillPoint.rear = -1;
}
//! [21]*/

void GraffitiArea::deSelectAll()
{
    pencil = false;
    eraser = false;
    line = false;
    rectangle = false;
    ellipse = false;
    fill = false;
    text = false;
    colorSelection = false;
    insertImage = false;
    modified = false;
    scribbling = false;
    erasing = false;
}

void GraffitiArea::print()
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
 
    QPrintDialog *printDialog = new QPrintDialog(&printer, this);
//! [21] //! [22]
    if (printDialog->exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0, 0, image);
    }
#endif // QT_NO_PRINTER
}
//! [22]
