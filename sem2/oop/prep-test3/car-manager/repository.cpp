#include "repository.h"
#include <fstream>
#include <fstream>


void Repository::load() {
	std::ifstream file("cars.txt");
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file");
	}

	std::string line;
	while (std::getline(file, line)) {
		size_t pos = 0;
		std::string make, model, color;
		int year;
		
		pos = line.find(',');
		make = line.substr(0, pos);
		line.erase(0, pos + 1);
		pos = line.find(',');
		model = line.substr(0, pos);
		line.erase(0, pos + 1);
		pos = line.find(',');
		year = std::stoi(line.substr(0, pos));
		color = line.substr(pos + 1);

		Car car = Car(make, model, year, color);
		cars.emplace_back(car);
	}

	file.close();
}

vector<Car> Repository::getAllCars() const {
	return this->cars;
}