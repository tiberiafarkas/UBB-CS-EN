#include "carmanager.h"
#include "service.h"

carmanager::carmanager(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	this->populateCarsList();

	connect(ui.ShowCars, &QPushButton::clicked, this, &carmanager::on_showCarsButton_clicked);
	connect(ui.ShowManufacture, &QPushButton::clicked, this, &carmanager::on_showManufactureButton_clicked);
}

carmanager::~carmanager()
{}

void carmanager::populateCarsList() {
	ui.CarsList->clear();
	Service service;
	vector<Car> cars = service.getAllCars();
	for (auto car : cars) {
		ui.CarsList->addItem(QString::fromStdString(car.toString()));
		ui.CarsList->item(ui.CarsList->count() - 1)->setForeground(QColor(QString::fromStdString(car.getColor())));
	}
}

void carmanager::on_showCarsButton_clicked()
{
	ui.CarsList->clear();
	Service service;
	vector<Car> cars = service.getAllCars();
	this->populateCarsList();
}

void carmanager::on_showManufactureButton_clicked()
{
	ui.CarsList->clear();
	Service service;
	string make = ui.ManufactureInput->text().toStdString();
	vector<Car> cars = service.getCarByMake(make);
	int count = cars.size();
	//the button will show "Number of cars:" count
	ui.CarsNumber->setText(QString::fromStdString("Number of cars: " + std::to_string(count)));
	for (const auto& car : cars) {
		ui.CarsList->addItem(QString::fromStdString(car.toString()));
	}
}
