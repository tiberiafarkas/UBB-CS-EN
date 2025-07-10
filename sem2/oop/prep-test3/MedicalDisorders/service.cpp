#include "service.h"
#include <algorithm>
#include <sstream>
#include <iostream>

vector<Disorder> Service::getAllDisorders() {
	vector<Disorder> disorders = this->repo.getAllDisorders();
	sort(disorders.begin(), disorders.end(), [](Disorder a, Disorder b) {
		return a.getCategory() < b.getCategory();
		});

	return disorders;
}

vector<Disorder> Service::getCertainDisorders(string field) {
	vector<Disorder> disorders;

	for (auto d : repo.getAllDisorders()) {
		string category = d.getCategory();
		string name = d.getName();

		if (category.find(field) != string::npos || name.find(field) != string::npos) {
			std::cout << d.getCategory() << std::endl;
			disorders.emplace_back(d);
		}
	}
	return disorders;
}

vector<string> Service::getSymptomps(string name) {
	vector<Disorder> disorders = this->repo.getAllDisorders();
	vector<string> symptomps;
	bool found = false;
	for (auto d : disorders) {
		if (d.getName() == name) {
			found = true;
			std::istringstream iss(d.getSymptomps());
			string s;
			while (getline(iss, s, ',')) {
				symptomps.emplace_back(s);
			}
		}
	}

	if (!found) {
		throw std::exception("no such disorder!");
	}

	return symptomps;
}