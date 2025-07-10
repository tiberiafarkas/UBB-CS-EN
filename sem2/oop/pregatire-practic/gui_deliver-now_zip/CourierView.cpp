#include "CourierView.h"
#include "Courier.h"
#include <algorithm>
#include <vector>
#include <QString> 

CourierView::CourierView(Service& service, Courier& courier, QWidget* parent)
    : QMainWindow(parent), service(service), courier(courier), packagesList(nullptr)
{
    service.attach(this);
    ui.setupUi(this);
    packagesList = ui.listWidget;
    setWindowTitle(QString::fromStdString(courier.getName()));

    QString zoneInfo = "Zone: Center(" + QString::number(courier.getZone().center) + "), Radius(" + QString::number(courier.getZone().radius) + ")";
    ui.label->setText(zoneInfo);

    selectedStreet = "All";
    ui.zoneComboBox->addItem(QString("All"));
    for (const auto& street : courier.getStreets())
    {
        ui.zoneComboBox->addItem(QString::fromStdString(street));
    }

    QObject::connect(ui.zoneComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [this]() {
        selectedStreet = ui.zoneComboBox->currentText().toStdString();
        populatePackagesList();
    });

    QObject::connect(ui.deliverButton, &QPushButton::clicked, [&,this]() {
        QListWidgetItem* item = packagesList->currentItem();
        if (item == nullptr)
        {
            return;
        }

        std::string packageInfo = item->text().toStdString();
        int spaceIndex = packageInfo.find(" - ");
        std::string packageSender = packageInfo.substr(0, spaceIndex);
        std::string packageAddress = packageInfo.substr(spaceIndex + 3, packageInfo.size());
        service.deliverPackage(packageSender, packageAddress);
    });

    populatePackagesList();
}

CourierView::~CourierView()
{
    service.detach(this);
}

void CourierView::populatePackagesList()
{
    packagesList->clear();
    std::vector<Package> courierPackages;

    for (const auto& package : service.getAllPackages())
    {
        const auto& streets = courier.getStreets(); // Get the streets from the courier object
        bool isInStreets = std::find(streets.begin(), streets.end(), package.getAddress()) != streets.end();
        bool isInZone = courier.isWithinZone(package.getLocation());

        if (!package.getStatus() && (isInStreets || isInZone) && (selectedStreet == "All" || selectedStreet == package.getAddress()))
        {
            courierPackages.push_back(package);
        }
    }

    for (const auto& package : courierPackages)
    {
        packagesList->addItem(QString::fromStdString(package.toString()));
    }
}


void CourierView::update()
{
    populatePackagesList();
}

