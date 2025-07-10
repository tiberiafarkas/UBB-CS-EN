#include "repository.h"
#include <sstream>

using std::getline;

void Repository::load() {
	std::ifstream file("medical.txt");
	if (!file) {
		throw std::exception("file could not be open!");
	}

	string line;
	string company, name, symptomps;
	while ( getline(file, line)) {
		std::istringstream iss(line);
		getline(iss, company, '|');
		getline(iss, name, '|');
		getline(iss, symptomps, '|');

		Disorder disorder = { company, name, symptomps };
		disorders.emplace_back(disorder);
	}
}

vector<Disorder> Repository::getAllDisorders() {
	return this->disorders;
}