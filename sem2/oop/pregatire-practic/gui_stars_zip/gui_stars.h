#pragma once

#include <QWidget>
#include <QTableView>
#include <QCheckBox>
#include <QSortFilterProxyModel>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include "starsModels.h"
#include "Service.h"
#include "ViewStarsWindow.h"

class AstronautWindow : public QWidget {
    Q_OBJECT
private:
    QCheckBox* constellations{};
    Astronaut aust;
    Service& service;
    QTableView* table;
    starsModel* stars;
    QSortFilterProxyModel* model;
    QLineEdit* nameOfStarLineEdit, * raEdit, * decEdit, * diameterEdit, * starNameFilter;
    QPushButton* addStarButton, * viewButton;
    QListWidget* filteredStars;
public:
    AstronautWindow(Astronaut aust, Service& service, starsModel* model);
public slots:
    void setup();
    void showConstellationsFiltered();
    void addStar();
    void populateList();
    void viewStars();
};
