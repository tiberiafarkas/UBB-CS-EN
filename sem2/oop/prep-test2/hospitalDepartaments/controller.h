#pragma once
#include "HospitalDepartment.h"
#include <vector>

using std::vector;
using std::string;

class Controller {
private:
	vector<HospitalDepartment*> departments;

public:
	Controller();
	~Controller();
	void addDepartment(HospitalDepartment* d);
	vector<HospitalDepartment*> getAllDepartmets();
	vector<HospitalDepartment*> getAllEfficientDepartments();
	void writeToFile(const string& filename);
};