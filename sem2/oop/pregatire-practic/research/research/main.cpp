#include "research.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
	Service service;
	IdeasTableView* model = new IdeasTableView(service);

	for (auto& researcher : service.getResearchers()) {
		research* window = new research(researcher, service, model);
		window->show();
	}

    return app.exec();
}
