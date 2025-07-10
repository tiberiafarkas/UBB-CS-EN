#include "carmanager.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    carmanager w;
    w.show();
    return a.exec();
}
