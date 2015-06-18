#include "glplot.h"
#include "glwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    glPlot w;
    w.show();

    return a.exec();
}
