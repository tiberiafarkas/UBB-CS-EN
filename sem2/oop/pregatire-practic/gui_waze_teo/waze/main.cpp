//#include "waze.h"
#include <QtWidgets/QApplication>
#include "repository.h"
#include "DriverView.h"
#include "MapView.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Repository repository{};

    for (auto& d : repository.getDrivers())
    {
		DriverView* driverView = new DriverView{ d, repository };
		driverView->show();
	}

    MapView* mapView = new MapView{ repository };
    mapView->show();

    return a.exec();
}
