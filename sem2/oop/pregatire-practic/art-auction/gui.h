#pragma once  

#include "service.h"  
#include "observer.h"  
#include <QWidget> // Change from QWidget to QMainWindow  

class guiWidget : public QWidget, public Observer 
{
	Q_OBJECT

public:
	guiWidget(Service& service, User user);
	~guiWidget() override;
	void update() override;

private:
	Service& service;
	User user;

public slots:
	void comboBoxChanged();
	void addButtonClicked();
	void populateList();
	void bidUser();
};
