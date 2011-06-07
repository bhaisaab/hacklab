#include "window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Bresenham's Circle Algo in Qt");

    QWidget* centralWidget = new QWidget(this);

    drawButton = new QPushButton("Draw", centralWidget);
   // drawStepByStepButton = new QPushButton("Step In", centralWidget);

    connect(drawButton, SIGNAL(clicked()),
            this, SLOT(draw()));

    redraw = new QCheckBox("Redraw Display", centralWidget);
    redraw->setTristate(false);
    redraw->setCheckState(Qt::Checked);

    connect(redraw, SIGNAL(stateChanged(int)),
            this, SLOT(redrawToggle(int)));

    progressBar = new QProgressBar(this);
    progressBar->setValue(0);

    statusBar = new QStatusBar(centralWidget);
    setStatusBar(statusBar);

    infoLabel = new QLabel("Circle Drawing Algorithm, in C++ using Qt. \nAuthor: \nRohit Yadav & Abhishek Kumar \nCSE PartIII, \n2009-2010.", centralWidget);
    infoLabel->setWordWrap(true);

    display = new DisplayWidget(centralWidget);
    connect(display, SIGNAL(updateProgressBar(float)),
            this, SLOT(updateProgressBar(float)));
    connect(display, SIGNAL(mousePos(QPoint)),
            this, SLOT(updateMousePos(QPoint)));

    scrollArea = new QScrollArea(this);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(display);

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(scrollArea, 10);
    vbox->addWidget(progressBar, 1);

    QVBoxLayout *vbox1 = new QVBoxLayout();
    vbox1->addWidget(redraw,1);
    vbox1->addWidget(drawButton, 1);
    vbox1->addWidget(infoLabel, 1);

    QHBoxLayout *hbox = new QHBoxLayout(centralWidget);
    hbox->addLayout(vbox, 10);
    hbox->addLayout(vbox1, 1);

    setCentralWidget(centralWidget);
}

void Window::draw()
{
    display->drawLine();
}

void Window::updateProgressBar(float val)
{
    progressBar->setValue((int) val * 100);
}

void Window::redrawToggle(int m)
{
   if( m > 0 )
       display->redraw = true;
   else
       display->redraw = false;
}

void Window::updateMousePos(QPoint pos)
{
    QString temp;
    temp.sprintf("Current/Last Mouse Pos: (%d, %d)", pos.x(), pos.y());
    statusBar->showMessage(temp);
}

