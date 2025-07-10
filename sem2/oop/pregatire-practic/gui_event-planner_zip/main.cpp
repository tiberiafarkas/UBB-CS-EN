#include <QApplication>
#include <QPushButton>
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Service serv;
    serv.readFromFileEvent();
    serv.readFromFilePers();

    for(auto &i:serv.getPersons())
    {
        auto *gui =new GUI(serv, i);
        gui->show();

    }

    return QApplication::exec();
}
