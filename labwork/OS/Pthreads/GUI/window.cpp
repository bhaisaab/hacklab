#include "window.h"
#include <stdio.h>
#include <QDebug>

Window::Window(QWidget *parent)
       : QMainWindow(parent)
{
    setWindowTitle("Matrix Comparision");

    QWidget* centralWidget = new QWidget(this);

    display = new Graph(centralWidget);

    scrollArea = new QScrollArea(this);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(display);

    statusBar = new QStatusBar(centralWidget);
    setStatusBar(statusBar);

    button = new QPushButton("Run Matrix Programs", centralWidget);

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
    x = 50;
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

    fp = fopen("/home/rohit/TestCube/OS LAB/3.\ Pthreads MatMult/input", "w");

    fprintf(fp, "%d %d\n", size, size);

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            fprintf(fp, "1 ");
        }
        fprintf(fp, "\n");
    }

    fprintf(fp, "%d %d\n", size, size);

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            fprintf(fp, "1 ");
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

void Window::runProgram(void)
{

  createInputFile(matrixSize);
  char *thr_Path = "/home/rohit/thread";
  char *sin_Path = "/home/rohit/single";

  long sin = spoof(1, sin_Path);
  long thr = spoof(1, thr_Path);

  qDebug() << "Single: "<< sin;
  qDebug() << "Thread:" << thr;

  sin = sin * 3500 / 750;
  thr = thr * 3500 / 750;

  display->drawPixel(x, 750 - sin, 0, matrixSize);
  display->drawPixel(x, 750 - thr, 1, matrixSize);

  if(thr < sin){
      display->drawSpot(x, 750-sin, 750-thr);
  }

  matrixSize += 5;
  x += 30;
}
