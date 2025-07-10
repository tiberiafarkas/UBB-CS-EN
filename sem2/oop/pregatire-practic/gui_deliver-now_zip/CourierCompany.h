#include "Service.h"
#include "Courier.h"
#include "Package.h"
#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QFormLayout>
#include <QComboBox>

#include "Observer.h"

class CourierCompany : public QWidget, public Observer
{
    Q_OBJECT

public:
    CourierCompany(Service& service, QWidget* parent = nullptr);
    ~CourierCompany();

private:
    Service& service;
    QListWidget* packagesList;
    void populatePackagesList();
    void update() override;
};