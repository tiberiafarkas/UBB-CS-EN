#include "MedicalAnalysis.h"

bool BMI::isResultOk() {
	return value >= 18.5 && value <= 25;
}

std::string BMI::toString() {
	return "Date: " + date + ", BMI: " + std::to_string(value) + ", Result: " + (isResultOk() ? "OK" : "Not OK");
}

bool BP::isResultOk() {
	return systolicValue >= 90 && systolicValue <= 119 && diastolicValue >= 60 && diastolicValue <= 80;
}

std::string BP::toString() {
	return "Date: " + date + ", BP: " + std::to_string(systolicValue) + "/" + std::to_string(diastolicValue) + ", Result: " + (isResultOk() ? "OK" : "Not OK");
}
