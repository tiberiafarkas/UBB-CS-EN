#include "controller.h"
#include <exception>
#include <fstream>
#include <algorithm>

Controller::Controller() {
	//add some default buildings
	buildings.push_back(new Block("Street 1", 1980, 100, 82));
	buildings.push_back(new Block("Street 2", 1990, 100, 4));
	buildings.push_back(new Block("Street 3", 2000, 100, 75));
	buildings.push_back(new House("Street 4", 1920, "Villa", true));
	buildings.push_back(new House("Street 5", 1930, "Villa", false));
	buildings.push_back(new House("Street 6", 2000, "Villa", false));
}

Controller::~Controller() {
	for (auto building : buildings) {
		delete building;
	}
}

void Controller::addBuilind(Building* building) {
	for (auto b : buildings) {
		if (b->getAddress() == building->getAddress()) {
			throw std::exception("Building already exists");
		}
	}

	buildings.push_back(building);
}

vector<Building*> Controller::getAllBuildings() {
	return buildings;
}

vector<Building*> Controller::getAllToBeRestored() {
	vector<Building*> toBeRestored;
	for (auto building : buildings) {
		if (building->mustBeRestored()) {
			toBeRestored.push_back(building);
		}
	}
	return toBeRestored;
}

vector<Building*> Controller::getAllToBeDemolished() {
	vector<Building*> toBeDemolished;
	for (auto building : buildings) {
		if (building->canBeDemolished()) {
			toBeDemolished.push_back(building);
		}
	}
	return toBeDemolished;
}

vector<Building*> Controller::getSortedByYear() {
	vector<Building*> sortedBuildings = this->getAllBuildings();
	std::sort(sortedBuildings.begin(), sortedBuildings.end(), [](Building* a, Building* b) {
		return a->getConstructionYear() < b->getConstructionYear();
		});
	return sortedBuildings;
}

void Controller::writeToFile(vector<Building*> buildings, const std::string& type) {
	if (type == "restored") {
		writeRestored("restored.txt", buildings);
	}
	else if (type == "demolished") {
		writeDemolished("demolished.txt", buildings);
	}
	else {
		throw std::exception("Invalid type");
	}
}

void Controller::writeRestored(const std::string& filename, vector<Building*> buildings) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		throw std::exception("Could not open file");
	}
	for (auto building : buildings) {
		file << building->toString();
	}
	file.close();
}

void Controller::writeDemolished(const std::string& filename, vector<Building*> buildings) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		throw std::exception("Could not open file");
	}
	for (auto building : buildings) {
		file << building->toString();
	}
	file.close();
}