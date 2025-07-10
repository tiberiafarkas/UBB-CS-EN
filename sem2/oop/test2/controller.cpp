#include "controller.h"
#include <fstream>
#include <exception>
#include <algorithm>

using std::vector;
using std::string;

Controller::Controller() {
	appliances.push_back(new Refrigerator("R1", "A++", true)); //80KW
	appliances.push_back(new Refrigerator("R2", "A", false)); //90KW
	appliances.push_back(new Refrigerator("R3", "A++", false)); //60KW
	appliances.push_back(new Refrigerator("R4", "A", true)); //110KW
	appliances.push_back(new DishWasher("DW3", 6)); //120KW
	appliances.push_back(new DishWasher("DW1", 0.5)); //10KW
	appliances.push_back(new DishWasher("DW2", 0.3)); //6KW
	
}

Controller::~Controller() {
	for (auto appliance : appliances) {
		delete appliance;
	}
}

void Controller::addAppliance(Appliance* appliance) {
	appliances.push_back(appliance);
}

vector<Appliance*> Controller::getAllAppliances() {
	return appliances;
}

vector<Appliance*> Controller::getAllWithConsumedElectricityLessThan(double maxElectricity) {
	vector<Appliance*> result;
	for (auto appliance : appliances) {
		if (appliance->consumedElectricity() < maxElectricity) {
			result.push_back(appliance);
		}
	}
	return result;
}

vector<Appliance*> Controller::getAllInefficientAppliances(double electricity) {
	vector<Appliance*> result;
	for (auto appliance : appliances) {
		if (appliance->consumedElectricity() > electricity) {
			result.push_back(appliance);
		}
	}
	return result;
}

void Controller::writeToFile(const string& fileName, double electricity) {
	std::ofstream fout(fileName);
	if (fout.is_open()) {
		vector<Appliance*> performantAppliances = getAllWithConsumedElectricityLessThan(electricity);
		//sorted by id
		std::sort(performantAppliances.begin(), performantAppliances.end(), [](Appliance* a, Appliance* b) {
			return a->getId() < b->getId();
		});
		for (auto appliance : performantAppliances) {
			fout << appliance->toString() << "\n";
		}
		fout.close();
	}
	else {
		throw std::exception("Could not open file");
	}
}
