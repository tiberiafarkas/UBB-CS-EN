#include "MedicalDisorders.h"
#include "service.h"
#include <sstream>

MedicalDisorders::MedicalDisorders(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
 
    ui.findDisorders->setText("Introduce the category or the name of a medical disorder:");
    ui.findSymptomps->setText("Introduce the name of the medical disorder:");

    connect(ui.disordersList, &QListWidget::itemPressed, this, &MedicalDisorders::on_showCategory);
    connect(ui.allDisorders, &QPushButton::clicked, this, &MedicalDisorders::on_showDisorders_clicked);
    connect(ui.showSymptoms, &QPushButton::clicked, this, &MedicalDisorders::on_showSymptomps_clicked);
    connect(ui.findDisorders, &QLineEdit::textChanged, this, &MedicalDisorders::on_filterDisorders);

	shown = false;

    this->populateList();
}

MedicalDisorders::~MedicalDisorders()
{}

void MedicalDisorders::populateList() {
    shown = true;
    Service service;
    vector<Disorder> disorders = service.getAllDisorders();

    ui.disordersList->clear();
    for (auto d : disorders) {
        ui.disordersList->addItem(QString::fromStdString(d.toString()));
    }
}

void MedicalDisorders::on_showCategory()
{
    if (shown == false)
        return;

    Service service;
    string category = ui.disordersList->currentItem()->text().toStdString();
    std::istringstream iss(category);
    getline(iss, category, ' ');

    ui.disordersList->clear();
    for (auto d : service.getAllDisorders()) {
        if (d.getCategory() == category) {
            ui.disordersList->addItem(QString::fromStdString(d.toString()));
			ui.disordersList->item(ui.disordersList->count() - 1)->setBackground(Qt::yellow);
        }
    }
}

void MedicalDisorders::on_showDisorders_clicked() {
    this->populateList();
}

void MedicalDisorders::on_showSymptomps_clicked() {
    Service service;
    string name = ui.findSymptomps->text().toStdString();

    try {
        vector<string> symptomps = service.getSymptomps(name);
        ui.disordersList->clear();
        for (auto s : symptomps) {
            ui.disordersList->addItem(QString::fromStdString(s));
        }
    }
    catch (std::exception e) {
        ui.findSymptomps->setText(QString::fromStdString("Error: " + std::string(e.what())));
    }

}

void MedicalDisorders::on_filterDisorders() {
    Service service;
    string field = ui.findDisorders->text().toStdString();
    vector<Disorder> disorders = service.getCertainDisorders(field);

    ui.disordersList->clear();
    for (auto d : disorders) {
        ui.disordersList->addItem(QString::fromStdString(d.toString()));
    }
}