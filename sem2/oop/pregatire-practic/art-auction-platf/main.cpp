#include "guiWidget.h"
#include <QtWidgets/QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	Service service; // Assuming you have a way to initialize your service
	for (auto user : service.getUsers()) {
		qDebug() << "User: " << QString::fromStdString(user.getName()) << ", Type: " << QString::fromStdString(user.getType()) << ", ID: " << user.getId();
		guiWidget *window = new guiWidget(service, user);
		window->show();
	}
    //guiWidget window;
    //window.show();
    return app.exec();
}
