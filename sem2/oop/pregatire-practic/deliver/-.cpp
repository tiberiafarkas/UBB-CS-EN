#include "gui.h"
#include <QMessageBox>
#include <QDebug>
#include <QColor>
#include <QGraphicsScene>

gui::gui(Service& service, Courier& courier) : service(service), courier(courier) {
    ui.setupUi(this);
	service.addObserver(this);
    
	if (courier.isCompany()) {
		setWindowTitle(QString::fromStdString("Company"));
		isCompany = true;
		ui.deliver->hide();
		ui.comboBox->hide();
		populateCompanyList();
		ui.courierPackages->hide();
		ui.graphicsView->hide();
	}
	else {
		if (courier.isImage()) {
			ui.addPackage->hide();
			ui.deliver->hide();
			ui.comboBox->hide();
			ui.recipient->hide();
			ui.address->hide();
			ui.x->hide();
			ui.y->hide();
			ui.graphicsView->show();
			ui.allPackages->hide();
			ui.courierPackages->hide();
			updateImage();
			setWindowTitle(QString::fromStdString("Image Courier"));
		}
		else {

			setWindowTitle(QString::fromStdString(courier.getName()));
			populateCourierList();
			ui.allPackages->hide();
			ui.recipient->hide();
			ui.address->hide();
			ui.graphicsView->hide();
			ui.addPackage->hide();
			ui.x->hide();
			ui.y->hide();

			for (int i = 0; i < ui.allPackages->count(); ++i) {
				QListWidgetItem* item = ui.allPackages->item(i);
				qDebug() << "IT: " << item->text();
			}
		}
	}

	for (auto street : courier.getStreets()) {
		ui.comboBox->addItem(QString::fromStdString(street));
	}
	
	connect(ui.comboBox, &QComboBox::currentTextChanged, this, &gui::comboBoxChanged);
	connect(ui.deliver, &QPushButton::clicked, this, &gui::deliverPackage);
	connect(ui.addPackage, &QPushButton::clicked, this, &gui::addPackage);
}

void gui::populateCourierList() {
	ui.courierPackages->clear();
	auto packages = service.getUnDeliveredPackages(courier);
	qDebug() << "Courier: " << QString::fromStdString(courier.getName()) << " has " << packages.size() << " packages " << courier.getPackages().size();
	for (auto package : packages) {
		qDebug() << package.getRecipient().c_str() << package.getAddress().c_str();
		ui.courierPackages->addItem(QString::fromStdString(package.getRecipient() + " | " + package.getAddress()));
	}
}

void gui::populateCompanyList() {
	ui.allPackages->clear();
	auto packages = service.getPackages();
	for (auto package : packages) {
		qDebug() << package.getRecipient() << package.getAddress();
		ui.allPackages->addItem(QString::fromStdString(package.getRecipient() + " | " + package.getAddress()));
	}
}

void gui::comboBoxChanged() {
	if (ui.comboBox->currentText().isEmpty()) {
		//QMessageBox::warning(this, "Warning", "Please select a package address.");
		return;
	}

	ui.courierPackages->clear();
	auto packages = service.getUnDeliveredPackages(courier);
	std::string selectedStreet = ui.comboBox->currentText().toStdString();

	for (auto& package : packages) {
		std::string address = package.getAddress();
		// assuming street is a substring of address
		if (address.find(selectedStreet) != std::string::npos) {
			ui.courierPackages->addItem(
				QString::fromStdString(package.getRecipient() + " | " + address)
			);
		}
	}
}

void gui::deliverPackage() {
	if (ui.courierPackages->currentItem() == nullptr) {
		QMessageBox::warning(this, "Warning", "Please select a package to deliver.");
		return;
	}
	auto selectedText = ui.courierPackages->currentItem()->text().toStdString();
	auto pos = selectedText.find("|");

	std::string recipient = selectedText.substr(0, pos - 1);
	std::string address = selectedText.substr(pos + 2);

	service.deliverPackage(recipient, address);
	populateCourierList();
	populateCompanyList();
	updateImage();
	service.notify();

	/*for (auto& package : service.getPackages()) {
		if (package.getRecipient() == recipient && package.getAddress() == address) {
			service.deliverPackage(package);
			return;
		}
	}*/
	return;
}

void gui::addPackage() {
	string recipient = ui.recipient->text().toStdString();
	string address = ui.address->text().toStdString();
	int x = ui.x->text().toInt();
	int y = ui.y->text().toInt();
	Package package(recipient, address, x, y);
	service.addPackage(package);
	
	ui.comboBox->addItem(QString::fromStdString(address));
	service.notify();
	populateCourierList();
	populateCompanyList();
}

void gui::updateImage() {
	QGraphicsScene* scene = new QGraphicsScene(this);
	ui.graphicsView->setScene(scene);
	ui.graphicsView->setSceneRect(-50, -50, 50, 50);

	/*scene->addEllipse(0, 0, 5, 5, QPen(Qt::black), QBrush(Qt::red));
	scene->addEllipse(50, 50, 5, 5, QPen(Qt::black), QBrush(Qt::blue));
	scene->addRect(-50, -50, 100, 100, QPen(Qt::green));*/

	//we want to plot the coordinates of the packages from service
	for (auto& package : service.getPackages()) {
		if (!package.isDelivered()) {
			qDebug() << package.getLocation().x << " " << package.getLocation().y;
			scene->addEllipse(package.getLocation().x, package.getLocation().y, 5, 5, QPen(Qt::black), QBrush(Qt::red));
		}

	}
}

void gui::update() {
	comboBoxChanged();
	populateCourierList();
	populateCompanyList();
	updateImage();
}

gui::~gui()
{}

