#include <QMainWindow>
#include <QListWidget>
#include "ui_CourierView.h"
#include "Service.h"
#include "Courier.h"
#include <vector>

class CourierView : public QMainWindow, Observer
{
    Q_OBJECT

public:
    CourierView(Service& service, Courier& courier, QWidget* parent = nullptr);
    ~CourierView();
    void populatePackagesList();

private:
    Ui::CourierViewClass ui;
    Service& service;
    Courier& courier;
    QListWidget* packagesList;
    std::string selectedStreet;
    void update() override;
};
