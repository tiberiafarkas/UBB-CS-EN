#include "Ui.h"
#include <iostream>

using std::cin;
using std::cout;

void UI::print_menu() {
	cout << "Choose an option:\n";
	cout << "1. add a school\n";
	cout << "2. get all schools\n";
	cout << "3. get 3 closest schools\n";
}

void UI::add() {
	string name, date;
	float lat, longit;
	cout << "name: ";
	cin >> name;
	cout << "latitue: ";
	cin >> lat;
	cout << "longitude: ";
	cin >> longit;
	cout << "date: ";
	cin >> date;
	School s(name, lat, longit, date);
	this->service.add(s);
}

void UI::print_schools() {
	DynamicArray<School> schools = this->service.getAll();
	for (int i = 0; i < schools.getSize(); ++i) {
		cout << schools[i].getName() << "|" << schools[i].getLat() << "|" << schools[i].getLong() << "|" << schools[i].getDate() << '\n';
	}
}

void UI::get_close_schools() {
	float lat, longit;
	cout << "lat: ";
	cin >> lat;
	cout << "longit: ";
	cin >> longit;

	DynamicArray<School> schools = this->service.getSchoolsSortedByDistanceandName(lat, longit);
	for (int i = 0; i < schools.getSize(); ++i) {
		cout << schools[i].getName() << "|" << schools[i].getLat() << "|" << schools[i].getLong() << "|" << schools[i].getDate() << '\n';
	}
}

void UI::run() {
	int option;
	while (true) {
		print_menu();
		cout << "\n introduce option: ";
		cin >> option;

		switch (option) {
		case 1:
			this->add();
			break;
		case 2:
			this->print_schools();
			break;
		case 3:
			this->get_close_schools();
			break;
		case 0:
			exit(0);
		default:
			cout << "Invalid command!\n";
		}
	}
}

