#include <QApplication>
#include <QPushButton>
#include "Service.h"
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Service serv;
    serv.readFromFileUsers();
    serv.readFromFileItems();
    for(auto &i:serv.getUsers())
    {
        auto *gui = new GUI(serv, i);
        gui->show();
    }
    return QApplication::exec();
}
