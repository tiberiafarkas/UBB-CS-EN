#pragma once
#include <string>

using std::string;

class HospitalDepartment {
protected:
	string hospitalName;
	int numberOfDoctors;

public:
	HospitalDepartment(const string& hospitalName, int numberOfDoctors) : hospitalName{ hospitalName }, numberOfDoctors{ numberOfDoctors } {};
	virtual ~HospitalDepartment() {};
	virtual bool isEfficient() = 0;
	virtual string toString();
	string getHospitalName();
};

class Surgery : public HospitalDepartment {
private:
	int numberOfPatients;

public:
	Surgery(const string& hospitalName, int numberOfDoctors, int numberOfPatients) :
		HospitalDepartment{ hospitalName, numberOfDoctors }, numberOfPatients{ numberOfPatients } {
	};
	~Surgery() {};
	bool isEfficient();
	string toString();
		
};

class NeonatalUnit : public HospitalDepartment {
private:
	int numberOfMothers;
	int numberOfNewborns;
	double averageGrade;

public:
	NeonatalUnit(const string& hospitalName, int numberOfDoctors, int numberOfMothers, int numberOfNewborns, double averageGrade) :
		HospitalDepartment{ hospitalName, numberOfDoctors }, numberOfMothers{ numberOfMothers }, numberOfNewborns{ numberOfNewborns }, averageGrade{ averageGrade } {
	};
	~NeonatalUnit() {};
	bool isEfficient();
	string toString();
};