#ifndef DDAWINDOW_H
#define DDAWINDOW_H

#include <QtGui>
#include "ddadisplay.h"

class DDAWindow : public QMainWindow
{
    Q_OBJECT

public:
    DDAWindow(QWidget *parent = 0);

public slots:
        void doDDA();
        void updateProgressBar(float);
        void redrawToggle(int);
        void updateMousePos(QPoint);

private:
    DDADisplay *display;

    QCheckBox *redraw;
    QPushButton *drawButton;
    QPushButton *drawStepByStepButton;

    QProgressBar *progressBar;
    QStatusBar *statusBar;

    QLabel *infoLabel;
    QScrollArea *scrollArea;
};

#endif // DDAWINDOW_H
