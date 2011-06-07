#ifndef VISUALISER_H
#define VISUALISER_H

#include <QtGui>

#include "gnattwidget.h"

class Visualiser : public QMainWindow
{
    Q_OBJECT

public:
    Visualiser(QWidget *parent = 0);
    void initGnatt();
    void runTask(int pid, int start, int duration);
    void setPeriod(int pid, int period);
    //~Visualiser();
private:
    QScrollArea *gnattScrollArea;
    QVBoxLayout *gnattWidgetLayout;
    GnattWidget *gnatt1;
    GnattWidget *gnatt2;
    GnattWidget *gnatt3;

    QPlainTextEdit *inputTextBox;
    QPushButton    *runButton;

private slots:        
    void runSimulation(void);

signals:
    void processInputData(QString);
};

#endif // VISUALISER_H
