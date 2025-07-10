#pragma once

#include <QMainWindow>
#include "ui_DriverView.h"
#include "repository.h"
#include "driver.h"
#include "observer.h"
#include <vector>


class DriverView : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	DriverView(Driver& driver, Repository& repository, QWidget *parent = nullptr); 
	~DriverView();

private:
	Ui::DriverViewClass ui;
	Repository& repository;
	Driver& driver;
	int radius = 10;
	std::vector<Report> currentReports;

	void update() override; 
	void connectSignalAndSlots(); 

};
