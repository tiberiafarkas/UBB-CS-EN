#pragma
#include <string>

using std::string;

class Appliance {
protected:
	string id;
public:
	Appliance(string id);
	~Appliance() {};
	string getId();
	virtual string toString();
	virtual double consumedElectricity() = 0;
};

class Refrigerator : public Appliance {
private:
	string electricityUsageClass;
	bool hasFreezer;
public:
	Refrigerator(string id, string electricityUsageClass, bool hasFreezer);
	~Refrigerator() {};
	double consumedElectricity();
	string toString();
};

class DishWasher : public Appliance {
private:
	double consumedElectricityForOneHour;
public:
	DishWasher(string id, double consumedElectricityForOneHour);
	~DishWasher() {};
	double consumedElectricity();
	string toString();
};

