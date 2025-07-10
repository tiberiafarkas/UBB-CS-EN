#include "appliance.h"
#include "iostream"

Appliance::Appliance(string id) : id{ id } {
}

string Appliance::toString() {
	return "Appliance ID: " + id + '\n';
}

string Appliance::getId() {
	return id;
}

Refrigerator::Refrigerator(string id, string electricityUsageClass, bool hasFreezer) : 
	Appliance(id), electricityUsageClass{ electricityUsageClass }, hasFreezer{ hasFreezer } {
}

double Refrigerator::consumedElectricity() {
	int x = 0;
	if (hasFreezer)
		x += 20;
	if (electricityUsageClass == "A") {
		//std::cout << 30 * 3 + x << '\n';
		return 30 * 3 + x;
	}
	else if (electricityUsageClass == "A++") {
		//std::cout << 30 * 2 + x << '\n';
		return 30 * 2 + x;
	}
}

string Refrigerator::toString() {
	return "Refrigerator\n" + id + "\nElectricity usage class : " + electricityUsageClass + "\nHas freezer : " + (hasFreezer ? "Yes" : "No") + '\n';
}

DishWasher::DishWasher(string id, double consumedElectricityForOneHour) :
	Appliance(id), consumedElectricityForOneHour{ consumedElectricityForOneHour } {
}

double DishWasher::consumedElectricity() {
	return consumedElectricityForOneHour * 20;
}

string DishWasher::toString() {
	return "DishWasher\n" + id + "\nConsumed electricity for one hour : " + std::to_string(consumedElectricityForOneHour) + '\n';
}




