#include "gui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Service service;

    for (auto& package : service.getPackages()) {
		qDebug() << "Package: " << QString::fromStdString(package.getRecipient())
			<< " | Address: " << QString::fromStdString(package.getAddress());
		package.setUnDelivered(); // Ensure all packages are marked as undelivered initially
	    for (auto& courier : service.getCuriers()) {
            for (auto& street : courier.getStreets()) {
				qDebug() << "Street: " << QString::fromStdString(street)
					<< " | Courier: " << QString::fromStdString(courier.getName());
                if (package.getAddress().find(street) != std::string::npos) {
                    courier.addPackage(&package);
					qDebug() << "Package for courier: " << QString::fromStdString(courier.getName())
						<< " | Recipient: " << QString::fromStdString(package.getRecipient())
						<< " | Address: " << QString::fromStdString(package.getAddress());
                    //break; // Avoid adding the same package multiple times
                }
            }
        }
	}

    for (auto& courier : service.getCuriers()) {
		qDebug() << "Courier: " << QString::fromStdString(courier.getName()) << "has packages " << courier.getPackages().size();
		gui *window = new gui(service, courier);
		window->show();
    }
    
    Courier c;
    c.setCompany();
    gui* company = new gui(service, c);
    company->show();

    Courier im;
    im.setImage();
    gui* image = new gui(service, im);
    image->show();
    return app.exec();
}
