#include "bppmprwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bPPMPRWidget w;
    w.show();
    return a.exec();
}
