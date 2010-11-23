#ifndef DDAWINDOW_H
#define DDAWINDOW_H

#include <QtGui>
#include "displaywidget.h"

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);

public slots:
        void draw();
        void updateProgressBar(float);
        void redrawToggle(int);
        void updateMousePos(QPoint);

private:
    DisplayWidget *display;

    QCheckBox *redraw;
    QPushButton *drawButton;
    QPushButton *drawStepByStepButton;

    QProgressBar *progressBar;
    QStatusBar *statusBar;

    QLabel *infoLabel;
    QScrollArea *scrollArea;
};

#endif // DDAWINDOW_H
