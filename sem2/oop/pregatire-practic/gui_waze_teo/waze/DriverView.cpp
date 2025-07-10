#include "DriverView.h"
#include <math.h>
#include <qmessagebox.h>

DriverView::DriverView(Driver& driver, Repository& repository, QWidget *parent)
	: QMainWindow(parent), driver{ driver }, repository{ repository }
{
	ui.setupUi(this);

	connectSignalAndSlots(); 

	repository.addObserver(this);

	this->setWindowTitle(QString::fromStdString(driver.getName())); 
	
	this->ui.listWithData->clear();
	for (auto r : repository.getReports())
	{
		if (abs(pow(driver.getLatitude() - r.getLatitude(), 2)) + abs(pow(driver.getLongitude() - r.getLongitude(), 2)) <= 100) 
			this->ui.listWithData->addItem(QString::fromStdString(r.toString())); 
	}

	if (driver.getStatus() == "knight")
	{
		this->setStyleSheet("background-color: #adebeb");
	}
	else if (driver.getStatus() == "grown-up")
	{
		this->setStyleSheet("background-color: #c6ffb3");	
	}
	else
	{
		this->setStyleSheet("background-color: #ffb3ff");
	}

	ui.currentLocationLabel->setText(QString::fromStdString(std::to_string(driver.getLatitude()) + "     " + std::to_string(driver.getLongitude())));
	ui.scoreLabel->setText(QString::fromStdString(std::to_string(driver.getScore())));
	ui.statusLabel->setText(QString::fromStdString(driver.getStatus()));

}

DriverView::~DriverView()
{
	repository.removeObserver(this); 
}

void DriverView::update()
{
	this->ui.listWithData->clear(); 
	for (auto r : repository.getReports()) 
	{
		if (abs(pow(driver.getLatitude() - r.getLatitude(), 2)) + abs(pow(driver.getLongitude() - r.getLongitude(), 2)) <= 100) 
			this->ui.listWithData->addItem(QString::fromStdString(r.toString()));
	}
}

void DriverView::connectSignalAndSlots()
{
	QObject::connect(ui.addButton, &QPushButton::clicked, [&]() {
		std::string description = ui.descriptionLineEdit->text().toStdString(); 
		int latitude = ui.latitudeLineEdit->text().toInt(); 
		int longitude = ui.longitudeLineEdit->text().toInt();
		std::string reporter = driver.getName();

		if (description == "" || (abs(pow(driver.getLatitude() - latitude, 2)) + abs(pow(driver.getLongitude() - longitude, 2)) > 400))
		{
			QMessageBox::critical(this, "Error", "Invalid data!");
			return;
		}
		
		Report r (description, reporter, latitude, longitude, 0) ;
		repository.addReport(r); 
	});

	QObject::connect(ui.radiusSlider, &QSlider::valueChanged, [&]() {
		radius = ui.radiusSlider->value(); 
		ui.radiusLabel->setText(QString::fromStdString(std::to_string(radius))); 

		this->ui.listWithData->clear();
		for (auto r : repository.getReports()) 
		{
			if (abs(pow(driver.getLatitude() - r.getLatitude(), 2)) + abs(pow(driver.getLongitude() - r.getLongitude(), 2)) <= radius * radius)  
				this->ui.listWithData->addItem(QString::fromStdString(r.toString())); 
		}	
	});

	QObject::connect(ui.northButton, &QPushButton::clicked, [&]() {
		driver.goNorth(); 
		ui.currentLocationLabel->setText(QString::fromStdString(std::to_string(driver.getLatitude()) + "     " + std::to_string(driver.getLongitude()))); 

		this->ui.listWithData->clear();
		for (auto r : repository.getReports())
		{
			if (abs(pow(driver.getLatitude() - r.getLatitude(), 2)) + abs(pow(driver.getLongitude() - r.getLongitude(), 2)) <= radius * radius)
				this->ui.listWithData->addItem(QString::fromStdString(r.toString()));
		}
		repository.notify();
	});
	
	QObject::connect(ui.southButton, &QPushButton::clicked, [&]() {
		driver.goSouth(); 
		ui.currentLocationLabel->setText(QString::fromStdString(std::to_string(driver.getLatitude()) + "     " + std::to_string(driver.getLongitude()))); 

		this->ui.listWithData->clear();
		for (auto r : repository.getReports())
		{
			if (abs(pow(driver.getLatitude() - r.getLatitude(), 2)) + abs(pow(driver.getLongitude() - r.getLongitude(), 2)) <= radius * radius)
				this->ui.listWithData->addItem(QString::fromStdString(r.toString()));
		}
		repository.notify();
	});
	
	QObject::connect(ui.eastButton, &QPushButton::clicked, [&]() {
		driver.goEast();
		ui.currentLocationLabel->setText(QString::fromStdString(std::to_string(driver.getLatitude()) + "     " + std::to_string(driver.getLongitude()))); 

		this->ui.listWithData->clear();
		for (auto r : repository.getReports())
		{
			if (abs(pow(driver.getLatitude() - r.getLatitude(), 2)) + abs(pow(driver.getLongitude() - r.getLongitude(), 2)) <= radius * radius)
				this->ui.listWithData->addItem(QString::fromStdString(r.toString()));
		}
		repository.notify(); 
	});
	
	QObject::connect(ui.westButton, &QPushButton::clicked, [&]() { 
		driver.goWest();
		ui.currentLocationLabel->setText(QString::fromStdString(std::to_string(driver.getLatitude()) + "     " + std::to_string(driver.getLongitude()))); 

		this->ui.listWithData->clear();
		for (auto r : repository.getReports())
		{
			if (abs(pow(driver.getLatitude() - r.getLatitude(), 2)) + abs(pow(driver.getLongitude() - r.getLongitude(), 2)) <= radius * radius)
				this->ui.listWithData->addItem(QString::fromStdString(r.toString()));
		}
		repository.notify();
	});

	// select report from list and increase report.validate
	/*QObject::connect(ui.validateButton, &QPushButton::clicked, [&]() {
		if (ui.listWithData->selectedItems().isEmpty())
			return;
		QListWidgetItem* item = ui.listWithData->selectedItems().at(0);
		std::string reportString = item->text().toStdString();
		std::string delimiter = " | ";
		std::string description = reportString.substr(0, reportString.find(delimiter)); 
		for (auto r : repository.getReports())
		{
			if (r.getDescription() == description)
			{
				try
				{
					r.increaseValidated(); 
				}
				catch (std::exception& e)
				{
					QMessageBox::critical(this, "Error", e.what()); 
					return; 
				}
				ui.scoreLabel->setText(QString::fromStdString(std::to_string(driver.getScore()))); 
				repository.notify(); 
				break;
			}
		}
	});*/

}