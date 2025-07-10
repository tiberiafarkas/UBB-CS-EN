#include "ui.h"
#include <iostream>

using std::cout;
using std::cin;
using std::vector;
using std::string;

void UI::printMenu() {
	cout << '\n';
	cout << "1. Add appliance\n";
	cout << "2. Show all appliances\n";
	cout << "3. Show all inefficient appliances\n";
	cout << "4. Write to file\n";
	cout << "0. Exit\n";
}

void UI::addAppliance() {
	string id;
	cout << "Enter appliance ID: ";
	cin.ignore();
	getline(cin, id);
	int type;
	cout << "Enter appliance type (1 for Refrigerator, 2 for DishWasher): ";
	cin >> type;
	if (type == 1) {
		string electricityUsageClass;
		bool hasFreezer;
		cout << "Enter electricity usage class (A, A++): ";
		cin >> electricityUsageClass;
		cout << "Does it have a freezer? (1 for Yes, 0 for No): ";
		cin >> hasFreezer;
		controller.addAppliance(new Refrigerator(id, electricityUsageClass, hasFreezer));
	}
	else if (type == 2) {
		double consumedElectricityForOneHour;
		cout << "Enter consumed electricity for one hour: ";
		cin >> consumedElectricityForOneHour;
		controller.addAppliance(new DishWasher(id, consumedElectricityForOneHour));
	}
	else {
		cout << "Invalid type\n";
	}
}

void UI::showAllAppliances() {
	vector<Appliance*> appliances = controller.getAllAppliances();
	for (auto appliance : appliances) {
		cout << appliance->toString() << "\n";
	}
}

void UI::showAllInefficientAppliances() {
	double maxElectricity;
	vector<Appliance*> ineffAppliances = controller.getAllInefficientAppliances(100);
	for (auto appliance : ineffAppliances) {
		cout << appliance->toString() << "\n";
	}
}

void UI::writeToFile() {
	double electricity;
	cout << "Enter maximum electricity consumption: ";
	cin >> electricity;
	try {
		controller.writeToFile("appliance.txt", electricity);
	} 
	catch (std::exception& e) {
		cout << e.what();
	}
}

void UI::run() {
	while (true) {
		printMenu();
		int choice;
		cout << "Enter your choice: ";
		cin >> choice;
		cout << '\n';
		switch (choice) {
		case 1:
			addAppliance();
			break;
		case 2:
			showAllAppliances();
			break;
		case 3:
			showAllInefficientAppliances();
			break;
		case 4:
			writeToFile();
			break;
		case 0:
			return;
		default:
			cout << "Invalid choice\n";
		}
	}
}