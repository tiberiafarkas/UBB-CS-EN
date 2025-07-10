#include "HospitalDepartment.h"

string HospitalDepartment::toString() {
	return "Hospital name: " + hospitalName + "\nNumber of doctors: " + std::to_string(numberOfDoctors) + '\n';
}

string HospitalDepartment::getHospitalName() {
	return this->hospitalName;
}

bool Surgery::isEfficient() {
	double prrocent = (double)numberOfPatients / (double)numberOfDoctors;
	if (prrocent >= 2)
		return true;
	else return false;
}

string Surgery::toString() {
	return "Surgery\nHospital name: " + hospitalName + "\nNumber of doctors: " + std::to_string(numberOfDoctors) + "\nNumber of patients: " + std::to_string(numberOfPatients) + '\n';
}

bool NeonatalUnit::isEfficient() {
	if (numberOfNewborns >= numberOfMothers && averageGrade > 8.5) {
		return true;
	}
	return false;
}

string NeonatalUnit::toString() {
	return "Neonatal Unit\nHospital name: " + hospitalName + "\nNumber of doctors:" + std::to_string(numberOfDoctors) + "\nNumber of mothers: " + std::to_string(numberOfMothers) + "\nNumber of newborns: " + std::to_string(numberOfNewborns) + "\nAverage grade: " + std::to_string(averageGrade) + '\n';
}