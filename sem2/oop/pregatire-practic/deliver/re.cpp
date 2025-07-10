#include "repository.h"
#include <fstream>

void Repository::load() {
	std::ifstream file("couriers.txt");
	if (file.is_open()) {
		Courier courier;
		while (file >> courier) {
			couriers.push_back(courier);
		}
		file.close();
	}
	std::ifstream packageFile("packages.txt");
	if (packageFile.is_open()) {
		Package package;
		while (packageFile >> package) {
			packages.push_back(package);
		}
		packageFile.close();
	}
}

void Repository::saveToFile() {
	std::ofstream file("couriers.txt");
	if (file.is_open()) {
		for (auto courier : couriers) {
			file << courier << '\n';
		}
		file.close();
	}
	std::ofstream packageFile("packages.txt");
	if (packageFile.is_open()) {
		for (auto package : packages) {
			packageFile << package << '\n';
		}
		packageFile.close();
	}
}