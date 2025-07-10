#pragma once
#include <string>
#include <vector>
#include "building.h"

using std::vector;

class Controller {
private:
	vector<Building*> buildings;

public:
	Controller();
	~Controller();
	void addBuilind(Building* building);
	vector<Building*> getAllBuildings();
	vector<Building*> getAllToBeRestored();
	vector<Building*> getAllToBeDemolished();
	vector<Building*> getSortedByYear();

	void writeToFile(vector<Building*> buildings, const std::string& type);
	void writeRestored(const std::string& filename, vector<Building*> buildings);
	void writeDemolished(const std::string& filename, vector<Building*> buildings);

};