#pragma once
#include "admin.h"
#include "user.h"

class MainWindow : public QWidget
{
	Q_OBJECT
private:
	//QVBoxLayout* layout;
	AdminWidget* adminWidget;
	UserWidget* userWidget;
	QPushButton* adminButton;
	QPushButton* userButton;
	Service& service;
public:
	MainWindow(Service& service, QWidget* parent = nullptr);
	~MainWindow();
	void chooseMode();
	void chooseFileType();
private slots:
	void showAdminWindow();
	void showUserWindow();
	void handleBack();
};
