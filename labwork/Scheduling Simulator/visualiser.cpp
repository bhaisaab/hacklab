#include "visualiser.h"
#include <QDebug>

Visualiser::Visualiser(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);

    gnatt1 = new GnattWidget();
    gnatt2 = new GnattWidget();
    gnatt3 = new GnattWidget();

    gnatt1->setColor(QColor(100, 200, 150));
    gnatt2->setColor(QColor(255, 66, 78));
    gnatt3->setColor(QColor(89, 153, 200));

    gnatt1->setPid(1);
    gnatt2->setPid(2);
    gnatt3->setPid(3);

    initGnatt();

    inputTextBox = new QPlainTextEdit;

    gnattWidgetLayout = new QVBoxLayout();
    gnattWidgetLayout->addWidget(gnatt1);
    gnattWidgetLayout->addWidget(gnatt2);
    gnattWidgetLayout->addWidget(gnatt3);

/*  gnattScrollArea = new QScrollArea(this);
    gnattScrollArea->setLayout(gnattWidgetLayout);
    gnattScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
*/

    runButton = new QPushButton("Run EDF", this);

    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(inputTextBox, 10);
    hbox->addWidget(runButton, 1);
    hbox->addWidget(new QLabel(QString("EDF Algorithm Simulator\n"
                                       "Usage: <PID> <Execution Time> <Period> <Phase>\n"
                                       "By Anshul, Nitin and Rohit")));

    QVBoxLayout *vbox = new QVBoxLayout(centralWidget);
    //vbox->addWidget(gnattScrollArea, 10);
    vbox->addLayout(gnattWidgetLayout, 10);
    vbox->addLayout(hbox, 1);
    vbox->addStretch(10);
    vbox->setMargin(10);

    setCentralWidget(centralWidget);

    connect(runButton, SIGNAL(clicked()),
            this, SLOT(runSimulation(void)));
}


void Visualiser::initGnatt()
{
    gnatt1->init();
    gnatt2->init();
    gnatt3->init();
}

void Visualiser::runSimulation()
{
    emit processInputData(inputTextBox->toPlainText());
}

void Visualiser::runTask(int pid, int start, int duration)
{
    switch(pid)
    {
        case 1: gnatt1->drawTask(start, duration); break;
        case 2: gnatt2->drawTask(start, duration); break;
        case 3: gnatt3->drawTask(start, duration); break;
    }
}

void Visualiser::setPeriod(int pid, int period)
{
    switch(pid)
    {
        case 1: gnatt1->setPeriod(period); break;
        case 2: gnatt2->setPeriod(period); break;
        case 3: gnatt3->setPeriod(period); break;
    }

}
