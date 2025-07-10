#pragma once
#include "appliance.h"
#include <vector>

using std::vector;

class Controller {
private:
	vector<Appliance*> appliances;

public:
	Controller();
	~Controller();
	void addAppliance(Appliance* appliance);
	vector<Appliance*> getAllAppliances();
	vector<Appliance*> getAllWithConsumedElectricityLessThan(double maxElectricity);
	vector<Appliance*> getAllInefficientAppliances(double electricity);
 	void writeToFile(const string& fileName, double electricity);
};