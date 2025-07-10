#include <iostream>
#include <string>
#include "Ui.h"
#include "Person.h"
#include "MedicalAnalysis.h"

Ui::Ui() {}
Ui::~Ui() {}

void Ui::PrintMenu() {
	std::cout << "1. Add analysis\n";
	std::cout << "2. Show all analyses\n";
	std::cout << "3. Show person illness\n";
	std::cout << "4. Save to file\n";
	std::cout << "0. Exit\n";
}

void Ui::addAnalysis() {
	std::cout << "Enter analysis type (1 for BMI, 2 for BP): ";
	int type;
	std::cin >> type;
	std::cout << "Enter date (YYYY.MM.DD): ";
	std::string date;
	std::cin >> date;
	if (type == 1) {
		readBMI(date);
	}
	else if (type == 2) {
		readBP(date);
	}
	else {
		std::cout << "Invalid type\n";
	}
};

void Ui::readBMI(std::string date) {
	std::cout << "Enter BMI value: ";
	double value;
	std::cin >> value;
	BMI* bmi = new BMI(date, value);
	person.addAnalysis(bmi);
}

void Ui::readBP(std::string date) {
	std::cout << "Enter systolic value: ";
	int systolicValue;
	std::cin >> systolicValue;
	std::cout << "Enter diastolic value: ";
	int diastolicValue;
	std::cin >> diastolicValue;
	BP* bp = new BP(date, systolicValue, diastolicValue);
	person.addAnalysis(bp);
}

void Ui::showAllAnalysis() {
	std::vector<MedicalAnalysis*> analyses = person.getAllAnalysis();
	for (auto& analysis : analyses) {
		std::cout << analysis->toString() << std::endl;
	}
}

void Ui::showPersonIll() {
	std::cout << "Enter month (1-12): ";
	int month;
	std::cin >> month;
	if (person.isIll(month)) {
		std::cout << "Person is ill in month " << month << std::endl;
	}
	else {
		std::cout << "Person is not ill in month " << month << std::endl;
	}
}

void Ui::saveToFile() {
	std::cout << "Enter file name: ";
	std::string fileName;
	std::cin >> fileName;
	std::cout << "Enter start date (YYYY.MM.DD): ";
	std::string date1;
	std::cin >> date1;
	std::cout << "Enter end date (YYYY.MM.DD): ";
	std::string date2;
	std::cin >> date2;
	person.writeToFile(fileName, date1, date2);
}

void Ui::start() {
	person.addEntries(); // Prepopulate with some entries
	while (true) {
		PrintMenu();
		std::cout << "Choose an option: ";
		int choice;
		std::cin >> choice;
		switch (choice) {
		case 1:
			addAnalysis();
			break;
		case 2:
			showAllAnalysis();
			break;
		case 3:
			showPersonIll();
			break;
		case 4:
			saveToFile();
			break;
		case 0:
			return;
		default:
			std::cout << "Invalid choice\n";
		}
		std::cout << std::endl;
	}
}