#include "vdcsketchpadwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VDCSketchpadWidget w;
    w.show();

    return a.exec();
}
