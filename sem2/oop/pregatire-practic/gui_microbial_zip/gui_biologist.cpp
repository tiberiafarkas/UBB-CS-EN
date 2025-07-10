#include "gui_biologist.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <utility>
#include "ViewBacteriaWindow.h"

BiologistWindow::BiologistWindow(Biologist biologist, Service& service, bacteriaModels* model)
    : biologist{ std::move(biologist) }, service{ service } {
    this->bacteria = model;
    this->model = new QSortFilterProxyModel();
    this->model->setSourceModel(this->bacteria);
    this->setWindowTitle(QString::fromStdString(this->biologist.getName()));
    this->setup();
}

void BiologistWindow::setup() {
    auto* layout = new QVBoxLayout();
    table = new QTableView();
    this->table->setModel(this->model);
    layout->addWidget(table);

    //combobox populated with all bacterial species the current biologist studies and when chosen the specific species, in table will only have that species
    comboBox = new QComboBox();
    comboBox->addItem("All");
    for (const auto& species : this->biologist.getStudiedSpecies()) {
        comboBox->addItem(QString::fromStdString(species));
    }
    layout->addWidget(comboBox);
    connect(comboBox, &QComboBox::currentTextChanged, this, &BiologistWindow::filterBySpecies);

    // Add input fields for new bacterium
    layout->addWidget(new QLabel("Name:", this));
    nameEdit = new QLineEdit(this);
    layout->addWidget(nameEdit);

    layout->addWidget(new QLabel("Species:", this));
    speciesEdit = new QLineEdit(this);
    layout->addWidget(speciesEdit);

    layout->addWidget(new QLabel("Size:", this));
    sizeEdit = new QLineEdit(this);
    layout->addWidget(sizeEdit);

    layout->addWidget(new QLabel("Diseases (comma-separated):", this));
    diseasesEdit = new QLineEdit(this);
    layout->addWidget(diseasesEdit);

    addBacteriaButton = new QPushButton("Add Bacterium", this);
    layout->addWidget(addBacteriaButton);
    connect(addBacteriaButton, &QPushButton::clicked, this, &BiologistWindow::addBacterium);


    //viewButton
    viewButton = new QPushButton("View", this);
    layout->addWidget(viewButton);
    QObject::connect(viewButton, &QPushButton::clicked, this, &BiologistWindow::viewBacterias);

    this->setLayout(layout);
}

void BiologistWindow::viewBacterias() {
    auto* viewWindow = new ViewBacteriaWindow(service, nullptr); // Use nullptr for parent to create a new top-level window
    viewWindow->setAttribute(Qt::WA_DeleteOnClose); // Ensure the window is deleted when closed
    viewWindow->show();
}



void BiologistWindow::filterBySpecies(const QString& species) {
    if (species == "All") {
        this->model->setFilterRegularExpression(QRegularExpression(".*", QRegularExpression::CaseInsensitiveOption));
    }
    else {
        this->model->setFilterRegularExpression(QRegularExpression(species, QRegularExpression::CaseInsensitiveOption));
    }
    this->model->setFilterKeyColumn(1);
}

void BiologistWindow::addBacterium() {
    QString name = nameEdit->text();
    QString species = speciesEdit->text();
    int size = sizeEdit->text().toInt();
    QString diseasesStr = diseasesEdit->text();

    try {
        service.addBacteria(name.toStdString(), species.toStdString(), size, diseasesStr.toStdString());
        this->bacteria->updateData(); // Update the model to reflect the new bacterium
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}