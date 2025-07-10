#include <QApplication>
#include <QPushButton>
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    PRepo prepo{};
    SRepo srepo{};
    Service srv(srepo);

    for(auto& p:prepo.getAll()){
        gui* g = new gui(srv,p);
        g->show();
    }


    return a.exec();
}
