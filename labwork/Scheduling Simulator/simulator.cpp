#include "simulator.h"
#include <QDebug>
#include <iostream>
using namespace std;

Simulator::Simulator(QObject* parent) : QObject(parent)
{
    ui = new Visualiser();
    ui->setMinimumSize(1280, 400);
    ui->setWindowTitle("EDF Task Sch. Algorithm");
    ui->show();

    connect(ui, SIGNAL(processInputData(QString)), this, SLOT(runEDF(QString)));

    /*
     *  EDF Algorithm Begins
     */
}

Simulator::~Simulator()
{
}

void Simulator::runEDF(QString input)
{
    a = new process[SLICE * sizeof(struct process)];//(process *)malloc(SLICE*sizeof(struct process));
    process extra[SLICE];

    flag = 0;
    heapsize=0;
    int option=1,l;
    int i,n=0,temp2,period;
    process temp;

    //Default PIDS = 3 for simulations
    n = 3;

    QStringList inputList  = input.split(" ");

    i = 0;
    while(i<(n*4))
    {
        temp.pid = inputList.at(i).toInt();;
        temp.execution_time = inputList.at(i+1).toInt();;
        period = inputList.at(i+2).toInt();
        temp.phase = inputList.at(i+3).toInt();
        i += 4;

        ui->setPeriod(temp.pid, period);

        //qDebug() << temp.pid << temp.execution_time << period << temp.phase << endl;

        temp.deadline=period+temp.phase;
        temp.period=period;
        while(temp.deadline<SLICE)
        {
                maxheapinsert(a,temp);
                temp.deadline+=temp.period;
                temp.start_time=temp.deadline-period;
        }
    }
    temp2=0;

    while(1)
    {
        temp=heapextractmax(a);
        l=0;
        flag=0;
        if(temp.pid==-1)
          return;
        while(temp2<(temp.deadline-temp.period))
        {
                extra[l]=temp;
                l++;
                temp=heapextractmax(a);
                if(temp.pid==-1)
                {
                        flag=1;
                        break;
                }
        }
        while(l!=0)
        {
                maxheapinsert(a,extra[l-1]);
                l--;
        }
        if(flag==0)
        qDebug()<<"\tstart time="<<temp2<<"\tend time="<<temp2+temp.execution_time
                <<"pid="<<temp.pid<<"\texecution time="<<temp.execution_time
                <<"\tperiod="<<temp.period;
        ui->runTask(temp.pid, temp2, temp.execution_time);
        temp2+=temp.execution_time;
    }

    delete a;
    return;
}

process Simulator::heapextractmax(process *a)
{

    process max;
    if(heapsize<1){
        //underflow
        max.pid=-1;
        max.execution_time=1;
        return max;
    }
    max=a[0];
    a[0]=a[heapsize-1];
    heapsize=heapsize-1;
    maxheapify(a,0);
    return max;
}

void Simulator::heapincreasekey(process *a,int i,process key)
{
    int parent;
    process temp;
    if(a[i].deadline>key.deadline)
    {
        cout<<"previous key is greater than this key"<<endl;
        return;
    }
    a[i]=key;
    while(i>0)
    {
        parent=(i-1)/2;
        if(a[i].deadline<a[parent].deadline)
        {
            temp=a[i];
            a[i]=a[parent];
            a[parent]=temp;
        }
        i=parent;
    }
}

void Simulator::maxheapinsert(process *a,process key)
{
    a[heapsize].execution_time=-1;
    a[heapsize].period=0;
    a[heapsize].deadline=0;
    heapsize++;
    heapincreasekey(a,heapsize-1,key);
}

void Simulator::maxheapify(process *a,int i)
{
    int left,right,smallest;
    process temp;
    left=2*i+1;
    right=2*i+2;
    if(left<heapsize && a[i].deadline>a[left].deadline)
    smallest=left;
    else
    smallest=i;
    if(right<heapsize && a[right].deadline<a[smallest].deadline)
    smallest=right;
    if(smallest!=i)
    {
        temp=a[i];
        a[i]=a[smallest];
        a[smallest]=temp;
        maxheapify(a,smallest);
    }
}
