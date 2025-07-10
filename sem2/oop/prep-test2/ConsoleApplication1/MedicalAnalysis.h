#pragma once
#include <string>

class MedicalAnalysis {
protected:
	std::string date;
public:
	MedicalAnalysis(std::string date) : date(date) {};
	~MedicalAnalysis() {};
	virtual bool isResultOk() = 0;
	virtual std::string toString() = 0;
	std::string getDate() { return date; }
};

class BMI : public MedicalAnalysis {
private:
	double value;
public:
	BMI(std::string date, double value) : MedicalAnalysis(date), value(value) {};
	~BMI() {};
	bool isResultOk() override;
	std::string toString();
};

class BP : public MedicalAnalysis {
private:
	int systolicValue;
	int diastolicValue;
public:
	BP(std::string date, int systolicValue, int diastolicValue) : MedicalAnalysis(date), systolicValue(systolicValue), diastolicValue(diastolicValue) {};
	~BP() {};
	bool isResultOk() override;
	std::string toString();
};
