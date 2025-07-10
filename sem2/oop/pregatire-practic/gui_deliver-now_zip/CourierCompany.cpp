#include "CourierCompany.h"

CourierCompany::CourierCompany(Service& service, QWidget* parent)
    : QWidget(parent), service(service)
{   
    service.attach(this);

    static auto* layout = new QHBoxLayout();
    static auto* c1 = new QWidget();
    static auto* c1Layout = new QVBoxLayout();

    static auto* label = new QLabel("Courier Company");
    label->setAlignment(Qt::AlignCenter);
    c1Layout->addWidget(label);
    
    static auto* formLayout = new QFormLayout();
    static auto* courierComboBox = new QComboBox();
    for (const auto& courier : service.getAllCouriers())
    {
        courierComboBox->addItem(QString::fromStdString(courier.getName()));
    }
    formLayout->addRow("Couriers", courierComboBox);
    
    static auto* recipientLineEdit = new QLineEdit();
    formLayout->addRow("Recipient", recipientLineEdit);

    static auto* addressLineEdit = new QLineEdit();
    formLayout->addRow("Address", addressLineEdit);

    static auto* locationXLineEdit = new QLineEdit();
    formLayout->addRow("Location X", locationXLineEdit);

    static auto* locationYLineEdit = new QLineEdit();
    formLayout->addRow("Location Y", locationYLineEdit);

    static auto* addButton = new QPushButton("Add");
    QObject::connect(addButton, &QPushButton::clicked, [&, this]() {
        std::string recipient = recipientLineEdit->text().toStdString();
        std::string address = addressLineEdit->text().toStdString();
        int locationX = locationXLineEdit->text().toInt();
        int locationY = locationYLineEdit->text().toInt();
        int courierIndex = courierComboBox->currentIndex();
        if (courierIndex == -1)
        {
            QMessageBox::warning(this, "Warning", "Please select a courier!");
            return;
        }
        Courier courier = this->service.getAllCouriers()[courierIndex];
        Location location{ locationX, locationY };
        Package package{ recipient, address, location, false };
        this->service.addPackage(package);
        populatePackagesList();
        QMessageBox::information(this, "Information", "Package added successfully!");
    });
    formLayout->addRow(addButton);
    
    c1Layout->addLayout(formLayout);
    c1->setLayout(c1Layout);

    layout->addWidget(c1);

    static auto* c2 = new QWidget();
    static auto* c2Layout = new QVBoxLayout();
    static auto* label2 = new QLabel("Packages");
    label2->setAlignment(Qt::AlignCenter);
    c2Layout->addWidget(label2);

    packagesList = new QListWidget();
    populatePackagesList();
    c2Layout->addWidget(packagesList);

    c2->setLayout(c2Layout);
    layout->addWidget(c2);

    setLayout(layout);
}

void CourierCompany::populatePackagesList()
{
    packagesList->clear();
    for (const auto& package : service.getAllPackages())
    {
        packagesList->addItem(QString::fromStdString(package.toString()) + " - " + (package.getStatus() ? "Delivered" : "Not delivered"));
    }
}

void CourierCompany::update()
{
    populatePackagesList();
}

CourierCompany::~CourierCompany()
{
    // Destructor implementation
}