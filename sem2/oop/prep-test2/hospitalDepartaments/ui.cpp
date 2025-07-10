#include "ui.h" 
#include <iostream>

using std::cout;
using std::cin;
using std::string;

void UI::printMenu() {
	cout << "1. Add department\n";
	cout << "2. Show all departments\n";
	cout << "3. Show all efficient departments\n";
	cout << "4. Save all the registered hospitals\n";
}

void UI::addDepartment() {
	int type, numberOfDoctors, numberOfPatients, numberOfMothers, numberOfNewborns;
	string hospitalName;
	double averageGrade;
	cout << "Enter type of hospital (1.Surgery/2.Neonatal unit): ";
	cin >> type;
	cout << "Hospital name: ";
	cin.get();
	getline(cin, hospitalName);
	cout << "Number of doctors: ";
	cin >> numberOfDoctors;

	if (type == 1) {
		cout << "Number of patients: ";
		cin >> numberOfPatients;
		Surgery* s = new Surgery(hospitalName, numberOfDoctors, numberOfPatients);
		controller.addDepartment(s);
	}
	else {
		cout << "Number of mothers: ";
		cin >> numberOfMothers;
		cout << "Number of newborns: ";
		cin >> numberOfNewborns;
		cout << "Average grade: ";
		cin >> averageGrade;

		NeonatalUnit* n = new NeonatalUnit(hospitalName, numberOfDoctors, numberOfMothers, numberOfNewborns, averageGrade);
		controller.addDepartment(n);
	}
}

void UI::showAllDepartments() {
	vector<HospitalDepartment*> dep = controller.getAllDepartmets();
	for (auto d : dep) {
		cout << d->toString() << '\n';
	}
}

void UI::showAllEfficientDepartments() {
	vector<HospitalDepartment*> dep = controller.getAllEfficientDepartments();
	for (auto d : dep) {
		cout << d->toString() << '\n';
	}
}

void UI::saveToFile() {
	controller.writeToFile("departments.txt");
}

void UI::start() {
	while (true) {
		int option;
		this->printMenu();
		cout << "Enter option: ";
		cin >> option;
		switch (option) {
		case 1:
			this->addDepartment();
			break;
		case 2:
			this->showAllDepartments();
			break;
		case 3:
			this->showAllEfficientDepartments();
			break;
		case 4:
			this->saveToFile();
			break;
		case 0:
			return;
		default:
			cout << "Invalid option!\n";
			break;
		}
	}
}