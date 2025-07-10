#include "Person.h"
#include <fstream>
#include <iostream>

void Person::addAnalysis(MedicalAnalysis* a) {
	analyses.push_back(a);
}

std::vector<MedicalAnalysis*> Person::getAllAnalysis() {
	return analyses;
}

std::vector<MedicalAnalysis*> Person::getAnalysisByMonth(int month) {
	std::vector<MedicalAnalysis*> result;
	for (auto& analysis : analyses) {
		if (analysis->getDate().substr(5, 2) == std::to_string(month)) {
			result.push_back(analysis);
		}
	}
	return result;
}

bool Person::isIll(int month) {
	for (auto& analysis : getAnalysisByMonth(month)) {
		std::cout << analysis->toString() << " " << analysis->isResultOk() << std::endl;
		if (!analysis->isResultOk()) {
			return true;
		}
	}
	return false;
}

std::vector<MedicalAnalysis*> Person::getAnalysesBetweenDates(std::string date1, std::string date2) {
	std::vector<MedicalAnalysis*> result;
	for (auto& analysis : analyses) {
		if (analysis->getDate() >= date1 && analysis->getDate() <= date2) {
			result.push_back(analysis);
		}
	}
	return result;
}

void Person::writeToFile(std::string fileName, std::string date1, std::string date2) {
	std::ofstream file(fileName);
	if (file.is_open()) {
		for (auto& analysis : getAnalysesBetweenDates(date1, date2)) {
			file << analysis->toString() << std::endl;
		}
		file.close();
	}
}

void Person::addEntries() {
	BMI* bmi1 = new BMI("2023.01.01", 22.5);
	BP* bp1 = new BP("2023.01.02", 120, 80);
	BMI* bmi2 = new BMI("2023.02.01", 23.0);
	BP* bp2 = new BP("2023.02.02", 130, 85);
	addAnalysis(bmi1);
	addAnalysis(bp1);
	addAnalysis(bmi2);
	addAnalysis(bp2);
}