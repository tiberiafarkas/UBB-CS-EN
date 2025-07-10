#pragma once
#include "controller.h"

class UI {
private:
	Controller controller;

public:
	UI() {};
	~UI() {};
	void printMenu();
	void addDepartment();
	void showAllDepartments();
	void showAllEfficientDepartments();
	void saveToFile();
	void start();
};