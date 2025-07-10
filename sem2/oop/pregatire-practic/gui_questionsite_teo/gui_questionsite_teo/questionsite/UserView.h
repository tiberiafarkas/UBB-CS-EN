#pragma once

#include <QMainWindow>
#include "ui_UserView.h"
#include "observer.h"
#include "service.h"

class UserView : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	UserView(User& user, Service& service, QWidget *parent = nullptr);
	~UserView();

private:
	Ui::UserViewClass ui;
	Service& service;
	User& user;

	void update() override;

	void connectSignalAndSlots();
};
