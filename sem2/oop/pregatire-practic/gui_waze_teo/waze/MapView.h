#pragma once

#include <QMainWindow>
#include "ui_MapView.h"
#include "repository.h"
#include "observer.h"

class MapView : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	MapView(Repository& repository, QWidget *parent = nullptr); 
	~MapView();

private:
	Ui::MapViewClass ui;
	Repository& repository;

	void update() override; 
	void paintEvent();
};
