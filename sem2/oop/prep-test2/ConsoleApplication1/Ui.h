#pragma once
#include "Person.h"

class Ui {
public:
	Person person;
	Ui();
	~Ui();
	void PrintMenu();
	void readBMI(std::string date);
	void readBP(std::string date);
	void addAnalysis();
	void showAllAnalysis();
	void showPersonIll();
	void saveToFile();
	void start();
};