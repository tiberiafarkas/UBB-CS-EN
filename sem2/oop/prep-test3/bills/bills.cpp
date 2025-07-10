#include "bills.h"
#include "service.h"
#include <iostream>

bills::bills(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	this->populateBillsTable();

	connect(ui.ShowAllBills, &QPushButton::clicked, this, &bills::on_showAllBillsButton_clicked);
	connect(ui.CalculateTotal, &QPushButton::clicked, this, &bills::on_calculateTotalButton_clicked);	
	connect(ui.PaidBills, &QCheckBox::toggled, this, &bills::on_showUnpaidBillsButton_clicked);

}

bills::~bills()
{}

void bills::populateBillsTable() {
	Service service;
	vector<Bill> bills = service.getBills();
	sort(bills.begin(), bills.end(), [](Bill& a, Bill& b) {
		return a.getCompany() < b.getCompany();
		});
	
	ui.BillsList->clear(); // Clear the list before populating it
	for (auto bill : bills) {
		ui.BillsList->addItem(QString::fromStdString(bill.toString()));

		if (bill.isPaid()) {
			ui.BillsList->item(ui.BillsList->count() - 1)->setForeground(Qt::green);
		}
		else {
			ui.BillsList->item(ui.BillsList->count() - 1)->setForeground(Qt::red);
		}

	}
}

void bills::on_showAllBillsButton_clicked() {
	this->populateBillsTable();
}

void bills::on_showUnpaidBillsButton_clicked(bool checked) {
	Service service;
	ui.BillsList->clear(); // Clear the list before populating it
	if (checked) {
		// Checkbox is checked => Show unpaid bills
		vector<Bill> unpaidBills = service.getUnpaidBills();
		for (auto& bill : unpaidBills) {
			ui.BillsList->addItem(QString::fromStdString(bill.toString()));
			ui.BillsList->item(ui.BillsList->count() - 1)->setForeground(Qt::red);
		}
	}
	else {
		// Checkbox is unchecked => Show paid bills
		vector<Bill> paidBills = service.getPaidBills();
		for (auto& bill : paidBills) {
			ui.BillsList->addItem(QString::fromStdString(bill.toString()));
			ui.BillsList->item(ui.BillsList->count() - 1)->setForeground(Qt::green);
		}
	}
}

void bills::on_calculateTotalButton_clicked() {
	Service service;
	string company = ui.IntroduceCompany->text().toStdString();
	try {
		float total = service.unpaidAmount(company);
		ui.TotalAmount->setText(QString::fromStdString("Total Amount: " + std::to_string(total)));
	}
	catch (const std::exception& e) {
		ui.TotalAmount->setText(QString::fromStdString("Error: " + std::string(e.what())));
		return;
	}
}