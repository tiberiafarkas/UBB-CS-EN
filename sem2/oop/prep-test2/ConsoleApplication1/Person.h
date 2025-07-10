#pragma once
#include <string>
#include "MedicalAnalysis.h"
#include <vector>

class Person {
private:
	std::string name;
	std::vector<MedicalAnalysis*> analyses;
public:
	Person() {};
	Person(std::string name) : name(name) {};
	~Person() {};
	void addAnalysis(MedicalAnalysis* a);
	std::vector<MedicalAnalysis*> getAllAnalysis();
	std::vector<MedicalAnalysis*> getAnalysisByMonth(int month);
	bool isIll(int month);
	std::vector<MedicalAnalysis*> getAnalysesBetweenDates(std::string date1, std::string date2);
	void writeToFile(std::string fileName, std::string date1, std::string date2);
	void addEntries();
};