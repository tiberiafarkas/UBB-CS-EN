#pragma once
#include "controller.h"

class UI {
private:
	Controller controller;
public:
	UI() = default;
	~UI() = default;
	void printMenu();
	void addBuilding();
	void showAllBuildings();
	void showAllSortedBuildings();
	void showToBeRestored();
	void showToBeDemolished();
	void start();
};