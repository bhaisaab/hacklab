#include <QtGui/QApplication>
#include "ddawindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DDAWindow w;
    w.show();

    return a.exec();
}
