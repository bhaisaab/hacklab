#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>
#include "graph.h"
#include "profiler/spoof.h"

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);

public slots:
    void updateMousePos(QPoint);
    void runProgram(void);
    void createInputFile(int size);
private:
    Graph *display;
    QStatusBar *statusBar;
    QScrollArea *scrollArea;
    QPushButton *button;
    int matrixSize;
    int x;
};

#endif // DDAWINDOW_H
