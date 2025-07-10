#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_bills.h"

class bills : public QMainWindow
{
    Q_OBJECT

public:
    bills(QWidget *parent = nullptr);
    ~bills();

private slots:
	void on_showAllBillsButton_clicked();
	void on_showUnpaidBillsButton_clicked(bool checked);
	void on_calculateTotalButton_clicked();
 
private:
    Ui::billsClass ui;
	void populateBillsTable();
};
