#include "DeliverNow.h"
#include "Courier.h"
#include "Service.h"
#include "CourierView.h"
#include "CourierCompany.h"
#include "Graph.h"
#include <QtWidgets/QApplication>
#include <ranges>
#include <algorithm>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    CourierRepository courierRepository;
    PackageRepository packageRepository;
    Service service{ packageRepository, courierRepository };
    std::vector<Package> packages = service.getAllPackages();
    auto couriers = service.getAllCouriers();

    if (couriers.empty()) {
        // Handle case when there are no couriers available
        return 0;
    }

    CourierCompany courierCompany{ service };
    courierCompany.show();

    Graph graph{ service };
    graph.show();

    // Make a copy of the packages vector
    std::vector<Package> packagesCopy = packages;

    for (auto && courier : couriers)
    {
        auto* courierView = new CourierView(service, courier);
        courierView->setWindowTitle(QString::fromStdString(courier.getName()));
        courierView->show();
    }

    return a.exec();
}
