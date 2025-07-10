#pragma once
#include <string>

class Car {
private:
	std::string manufacture, model, colour;
	int year;

public:
	//constructor
	Car();
	Car(const std::string& manufacture, const std::string& model, int year, const std::string& colour);

	//destructor 
	~Car();

	//getters
	std::string getManufacture() const;
	std::string getModel() const;
	int getYear() const;
	std::string getColour() const;

	/*void addCar(const std::string& manufacture, const std::string& model, int year, const std::string& colour);
	void removeCar(Car car);*/
};