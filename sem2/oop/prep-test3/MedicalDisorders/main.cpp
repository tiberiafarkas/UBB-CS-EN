#include "MedicalDisorders.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MedicalDisorders window;
    window.show();
    return app.exec();
}
