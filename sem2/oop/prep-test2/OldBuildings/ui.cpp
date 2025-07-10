#include "ui.h"
#include <iostream>

using std::cout;
using std::cin;
using std::string;

void UI::printMenu() {
	cout << "1. Add building\n";
	cout << "2. Show all buildings\n";
	cout << "3. Show buildings to be restored\n";
	cout << "4. Show buildings to be demolished\n";
	cout << "5. Show all buildings sorted by year\n";
	cout << "0. Exit\n";
}

void UI::addBuilding() {
	string address;
	int constructionYear;
	string type;
	bool isHistorical;
	int totalApartaments;
	int occupiedApartaments;
	string houseType;
	cout << "Enter address: ";
	cin >> address;
	cout << "Enter construction year: ";
	cin >> constructionYear;
	cout << "Enter type (block/house): ";
	cin >> type;
	if (type == "block") {
		cout << "Enter total apartaments: ";
		cin >> totalApartaments;
		cout << "Enter occupied apartaments: ";
		cin >> occupiedApartaments;
		try {
			controller.addBuilind(new Block(address, constructionYear, totalApartaments, occupiedApartaments));
		}
		catch (std::exception& e) {
			cout << e.what() << '\n';
			return;
		}
	}
	else if (type == "house") {
		cout << "Enter type of house: ";
		cin >> houseType;
		cout << "Enter is historical (1 for yes, 0 for no): ";
		cin >> isHistorical;
		try {
			controller.addBuilind(new House(address, constructionYear, houseType, isHistorical));
		}
		catch (std::exception& e) {
			cout << e.what() << '\n';
			return;
		}
	}
	else {
		cout << "Invalid type\n";
	}
}

void UI::showAllBuildings() {
	vector<Building*> buildings = controller.getAllBuildings();
	for (auto building : buildings) {
		cout << building->toString() << '\n';
	}
}

void UI::showAllSortedBuildings() {
	vector<Building*> buildings = controller.getSortedByYear();
	for (auto building : buildings) {
		cout << building->toString() << '\n';
	}
}

void UI::showToBeRestored() {
	vector<Building*> buildings = controller.getAllToBeRestored();
	try {
		controller.writeToFile(buildings, "restored");
	}
	catch (std::exception& e) {
		cout << e.what() << '\n';
		return;
	}
}

void UI::showToBeDemolished() {
	vector<Building*> buildings = controller.getAllToBeDemolished();
	try {
		controller.writeToFile(buildings, "demolished");
	}
	catch (std::exception& e) {
		cout << e.what() << '\n';
		return;
	}
}

void UI::start() {
	int option;
	while (true) {
		this->printMenu();
		cout << "Enter option: ";
		cin >> option;
		switch (option) {
			case 1:
				this->addBuilding();
				break;
			case 2:
				this->showAllBuildings();
				break;
			case 3:
				this->showToBeRestored();
				break;
			case 4:
				this->showToBeDemolished();
				break;
			case 5:
				this->showAllSortedBuildings();
				break;
			case 0:
				cout << "Exiting...\n";
				return;
			default:
				cout << "Invalid option\n";
				break;
		}
	}
}
