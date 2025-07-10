#pragma once
#include <QWidget>
#include <QTableView>
#include <QCheckBox>
#include <QSortFilterProxyModel>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QComboBox>
#include "bacteriaModels.h"
#include "Service.h"
#include <QRegularExpression>

class BiologistWindow : public QWidget {
    Q_OBJECT
private:
    Biologist biologist;
    Service& service;
    QTableView* table;
    bacteriaModels* bacteria;
    QSortFilterProxyModel* model;
    QPushButton* addBacteriaButton, * viewButton;
    QComboBox* comboBox;
    QLineEdit* nameEdit, * speciesEdit, * sizeEdit, * diseasesEdit;

public:
    BiologistWindow(Biologist biologist, Service& service, bacteriaModels* model);
public slots:
    void setup();
    void filterBySpecies(const QString& species);
    void addBacterium();
    void viewBacterias();
};