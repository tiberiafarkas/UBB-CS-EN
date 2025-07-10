#pragma once
#include <string>

using std::string;

class Car {
private:
	string make;
	string model;
	int year;
	string color;

public:
	Car(string make, string model, int year, string color) : make(make), model(model), year(year), color(color) {}
	~Car() {}
	string getMake();
	string getModel();
	int getYear();
	string getColor();
	string toString() const {
		return make + " " + model + " " + std::to_string(year) + " " + color;
	}
};