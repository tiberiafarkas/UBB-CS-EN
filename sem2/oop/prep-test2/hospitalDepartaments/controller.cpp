#include "controller.h"
#include <fstream>
#include <algorithm>

using std::string;
using std::vector;

Controller::Controller() {
	departments.push_back(new Surgery("Regina Maria", 15, 40));
	departments.push_back(new Surgery("Policlinica", 45, 20));
	departments.push_back(new NeonatalUnit("Spital Deva", 30, 15, 18, 8.9));
	departments.push_back(new NeonatalUnit("Spital Vaslui", 20, 26, 10, 7));
}

Controller::~Controller() {
	for (auto d : departments) {
		delete d;
	}
}

void Controller::addDepartment(HospitalDepartment* d) {
	departments.push_back(d);
}

vector<HospitalDepartment*> Controller::getAllDepartmets() {
	return departments;
}

vector<HospitalDepartment*> Controller::getAllEfficientDepartments() {
	vector<HospitalDepartment*> efficientDep;
	for (auto d : departments) {
		if (d->isEfficient()) {
			efficientDep.push_back(d);
		}
	}
	return efficientDep;
}

void Controller::writeToFile(const string& filename) {
	std::ofstream fout(filename);
	std::sort(departments.begin(), departments.end(), [](HospitalDepartment* a, HospitalDepartment* b) {
		return a->getHospitalName() < b->getHospitalName();
		}
	);

	for (auto d : departments) {
		fout << d->toString() << '\n';
	}
}