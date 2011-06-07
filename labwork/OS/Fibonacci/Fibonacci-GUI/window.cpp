#include "window.h"
#include <stdio.h>
#include <QDebug>

Window::Window(QWidget *parent)
       : QMainWindow(parent)
{
    setWindowTitle("Fibonacci Single Vs. PThread Vs. Java Threads");

    QWidget* centralWidget = new QWidget(this);

    display = new Graph(centralWidget);

    scrollArea = new QScrollArea(this);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(display);

    statusBar = new QStatusBar(centralWidget);
    setStatusBar(statusBar);

    button = new QPushButton("Run Fibonacci Programs", centralWidget);

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(scrollArea, 10);
    vbox->addWidget(button,1, Qt::AlignCenter);

    vbox->setMargin(0);

    QHBoxLayout *hbox = new QHBoxLayout(centralWidget);
    hbox->addLayout(vbox, 10);
    hbox->setMargin(0);

    setCentralWidget(centralWidget);

    connect(display, SIGNAL(mousePos(QPoint)),
            this, SLOT(updateMousePos(QPoint)));
    connect(button, SIGNAL(clicked()),
            this, SLOT(runProgram(void)) );

    matrixSize = 5;
    x = 75;
}


void Window::updateMousePos(QPoint pos)
{
    QString temp;
    temp.sprintf("Current/Last Mouse Pos: (%d, %d)", pos.x(), pos.y());
    statusBar->showMessage(temp);
}

void Window::createInputFile(int size)
{
    FILE* fp;

    fp = fopen("/home/rohit/input", "w");

    fprintf(fp, "%d\n", size);

    fclose(fp);
}

void Window::runProgram(void)
{
  if(x < 1600)
  {
  createInputFile(matrixSize);
  char *thr_Path = "/home/rohit/fibthread";
  char *sin_Path = "/home/rohit/fibsingle";
  char *jthr_Path = "/home/rohit/fibjthread.jar";

  long sin = spoof(1, sin_Path);
  long thr = spoof(1, thr_Path);
  long jthr = spoof(2, jthr_Path);

  qDebug() << "Single: "<< sin;
  qDebug() << "PThread:" << thr;
  qDebug() << "JavaThread:" << jthr;

  sin = sin * 600 / 500;
  thr = thr * 600 / 500;
  jthr = jthr * 600 / 500;

  display->drawPixel(x, 500 - sin - 10, 0, matrixSize);
  display->drawPixel(x, 500 - thr - 10, 1, matrixSize);
  display->drawPixel(x, 500 - jthr - 10, 2, matrixSize);

  if(thr < sin){
      display->drawSpot(x, 500-sin-10, 500-thr - 10);
  }

  matrixSize += 10;
  x += 40;
}
}
