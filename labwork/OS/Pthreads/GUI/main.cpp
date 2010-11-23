#include <QtGui/QApplication>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Window w;
    //w.setFixedSize(960, 800);
    w.show();

    return a.exec();
}
