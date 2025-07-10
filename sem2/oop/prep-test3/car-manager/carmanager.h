#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_carmanager.h"

class carmanager : public QMainWindow
{
    Q_OBJECT

public:
    carmanager(QWidget *parent = nullptr);
    ~carmanager();

private slots:
	void on_showCarsButton_clicked();
	void on_showManufactureButton_clicked();

private:
    Ui::carmanagerClass ui;
    void populateCarsList();
};
