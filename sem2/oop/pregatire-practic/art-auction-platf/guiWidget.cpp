#include "guiWidget.h"
#include <QMessageBox>
#include <sstream>
#include <QDebug>

using std::stringstream;

guiWidget::guiWidget(Service& service, User user) : service(service), user(user) {
	ui.setupUi(this);
	service.addObserver(this);
	setWindowTitle(QString::fromStdString(user.getName()));

	qDebug() << user.getType();

	for (auto item : service.getItems()) {
		ui.comboBox->addItem(QString::fromStdString(item.getCategory()));
	}

	if (user.getType() == "administrator") {
		isAdministrator = true;
		ui.inputDate->hide();
		ui.inputOffer->hide();
		ui.bid->hide();
	}
	else {
		isAdministrator = false;
		ui.inputName->hide();
		ui.inputCategory->hide();
		ui.inputPrice->hide();
		ui.addItem->hide();
	}
	
	populateList();

	connect(ui.comboBox, &QComboBox::currentTextChanged, this, &guiWidget::comboBoxChanged);
	connect(ui.addItem, &QPushButton::clicked, this, &guiWidget::addButtonClicked);
	connect(ui.bid, &QPushButton::clicked, this, &guiWidget::bidUser);
	connect(ui.itemList, &QListWidget::itemSelectionChanged, this, &guiWidget::showOffers);
}

void guiWidget::populateList() {
	ui.itemList->clear();
	auto items = service.getItems();
	qDebug() << "Populating list with items:";
	for (auto item : items) {
		qDebug() << item.getName().c_str() << item.getCategory().c_str() << item.getPrice();
		ui.itemList->addItem(QString::fromStdString(item.getName() + " " + item.getCategory() + " " + std::to_string(item.getPrice())));
		
		//ui.comboBox->addItem(QString::fromStdString(item.getCategory()));
	}
}

void guiWidget::comboBoxChanged() {
	if (ui.comboBox->currentText().isEmpty()) {
		QMessageBox::warning(this, "Error", "Please select a category.");
		return;
	}
	ui.itemList->clear();
	string category = ui.comboBox->currentText().toStdString();

	for (auto item : service.getItemsByCategory(category)) {
		ui.itemList->addItem(QString::fromStdString(item.getName() + " " + item.getCategory() + " " + std::to_string(item.getPrice())));
	}
}

void guiWidget::addButtonClicked() {
	if (!isAdministrator) {
		QMessageBox::warning(this, "Error", "You do not have permission to add items.");
		return;
	}
	QString name = ui.inputName->text();
	QString category = ui.inputCategory->text();

	try {
		service.addItem(name.toStdString(), category.toStdString(), ui.inputPrice->text().toInt(), {});
		ui.inputName->clear();
		ui.inputCategory->clear();
		ui.inputPrice->clear();

		ui.comboBox->addItem(category);
		service.notifyAllObservers();
	}
	catch (const std::exception& e) {
		QMessageBox::warning(this, "Error", e.what());
		return;
	}
	populateList();
}

void guiWidget::showOffers() {
	QList<QListWidgetItem*> it = ui.itemList->selectedItems();

	if (it.size() == 0)
		return;

	QListWidgetItem* item = it.first();
	QString text = item->text();
	QStringList parts = text.split(" ");

	string name = parts[0].toStdString();

	ui.seeOffers->clear();

	string category = parts[1].toStdString();
	for (auto item : service.getItemsByCategory(category)) {
		if (item.getName() == name) {
			for (const auto& offer : service.getOffers(item)) {
				ui.seeOffers->addItem(QString::fromStdString(std::to_string(std::get<0>(offer)) + " " + std::get<1>(offer) + " " + std::to_string(std::get<2>(offer))));
			}
			break;
		}
	}
}

void guiWidget::bidUser() {
	if (!isAdministrator)
		return;

	if (ui.itemList->currentItem() == nullptr) {
		QMessageBox::warning(this, "Error", "Please select an item to bid on.");
		return;
	}
	QString selectedItem = ui.itemList->currentItem()->text();
	QStringList parts = selectedItem.split(" ");

	string name = parts[0].toStdString();
	Item it;

	for (auto item : service.getItems()) {
		if (item.getName() == name) {
			it = item;
			break;
		}
	}

	int newPrice = ui.inputOffer->text().toInt();
	string date = ui.inputDate->text().toStdString();
	try {
		service.bid(it, user.getId(), date, newPrice);
		ui.inputOffer->clear();
		ui.inputDate->clear();
		service.notifyAllObservers();
	}
	catch (const std::exception& e) {
		QMessageBox::warning(this, "Error", e.what());
		return;
	}
	populateList();
}

void guiWidget::update() {
	comboBoxChanged();
	populateList();
}

guiWidget::~guiWidget() {
}

