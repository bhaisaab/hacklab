#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include <QWidget>

#include "visualiser.h"
#define SLICE 61
/* RUn for 60 secs or 1 min */

struct process
{
        int pid;
        int execution_time;
        int period;
        int start_time;
        int deadline;
        int phase;
};

class Simulator : public QObject
{
    Q_OBJECT

public:
    Simulator(QObject* parent = 0);
    ~Simulator();

private:
    Visualiser *ui;
    int heapsize;
    int flag;

    process *a;

    process heapextractmax(process *);
    void heapincreasekey(process *,int , process );
    void maxheapinsert(process *,process );
    void maxheapify(process *,int );

private slots:
    void runEDF(QString input);

//signals:
//    void processInputData(QString);

};

#endif // SIMULATOR_H
