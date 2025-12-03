#pragma once

#include <QtWidgets/QWidget>
#include "ui_gui.h"
#include "service.h"
#include "observer.h"

class gui : public QWidget, public Observer
{
    Q_OBJECT

public:
    gui(Department& dep, Service& serv, QWidget *parent = nullptr);
    ~gui();

private slots:
	void addVolunteer();
	void assignVolunteer();

private:
    Ui::guiClass ui;
	Service& service; 
    Department& dep;
    void populateList();
	void populateDepartmentList();
    void update();
    void updateSuitableVolunteersList();
};

