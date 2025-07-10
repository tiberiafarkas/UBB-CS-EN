#pragma once
#include <iostream>
#include "controller.h"

class UI {
private:
	Controller controller;

public:
	void printMenu();
	void addAppliance();
	void showAllAppliances();
	void showAllInefficientAppliances();
	void writeToFile();
	void run();
};