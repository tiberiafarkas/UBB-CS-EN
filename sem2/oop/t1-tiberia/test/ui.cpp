#include "ui.h"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;

void UI::printMenu()
{
	cout << "1. Add subscription\n";
	cout << "2. Show all subscriptions\n";
	cout << "3. Show active subscriptions given the current month\n";
	cout << "0. Exit\n";
}

void UI::addSubscription()
{
	string name, date;
	float fee;
	bool active;
	cout << "Name: ";
	cin >> name;
	cout << "Date: ";
	cin >> date;
	cout << "Fee: ";
	cin >> fee;
	cout << "Active (1/0): ";
	cin >> active;
	domain s{ name, date, fee, active };
	if (this->service.addSubscription(s))
		cout << "Subscription added successfully\n";
	else
		cout << "Subscription already exists\n";
}

void UI::showSubscriptions()
{
	DynamicArray<domain> subs = this->service.getSubscriptions();
	for (int i = 0; i < subs.getSize(); i++)
	{
		cout << subs[i].getName() << " | " << subs[i].getDate() << " | " << subs[i].getFee() << " | " << subs[i].isActive() << "\n";
	}
}

void UI::showActiveSubscriptions()
{
	string date;
	cout << "Date: ";
	cin >> date;
	DynamicArray<domain> subs = this->service.getActiveSubscriptions(date);
	float total_value = 0;
	for (int i = 0; i < subs.getSize(); i++)
	{
		cout << subs[i].getName() << " | " << subs[i].getDate() << " | " << subs[i].getFee() << " | " << subs[i].isActive() << "\n";
		total_value += subs[i].getFee();
	}
	cout << "\nTotal value: " << total_value << '\n';
}

void UI::run()
{
	this->service.getEntries();
	while (true) {
		this->printMenu();
		int cmd;
		cout << "\nCommand: ";
		cin >> cmd;
		cout << '\n';
		switch (cmd) {
		case 1:
			this->addSubscription();
			break;
		case 2:
			this->showSubscriptions();
			break;
		case 3:
			this->showActiveSubscriptions();
			break;
		case 0:
			exit(0);
		default:
			cout << "Invalid command\n";
		}
		cout << '\n';
	}
}