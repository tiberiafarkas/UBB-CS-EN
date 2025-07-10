#pragma once

#include <QtWidgets/QWidget>
#include "ui_gui.h"
#include "service.h"

class gui : public QWidget, public Observer {
    Q_OBJECT

public:
    gui(Service& service, Courier &courier);
    ~gui() override;

private:
    Ui::guiClass ui;
    Service& service;
    Courier& courier;
    bool isCompany;

private slots:
    void populateCourierList();
    void populateCompanyList();
    void comboBoxChanged();
	void deliverPackage();
    void update() override;
	void addPackage();
    void updateImage();

};

