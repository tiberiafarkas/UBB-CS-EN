#include "repository.h"
#include <fstream>

void Repository::load() {
	std::ifstream file("bills.txt");
	if (!file.is_open()) {
		throw std::runtime_error("Could not open bills.txt");
	}
	string line;
	while (std::getline(file, line)) {
		if (line.empty()) continue; // Skip empty lines
		size_t pos1 = line.find('|');
		size_t pos2 = line.find('|', pos1 + 1);
		size_t pos3 = line.find('|', pos2 + 1);
		if (pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos) {
			throw std::runtime_error("Invalid format in bills.txt");
		}
		string company = line.substr(0, pos1);
		string id = line.substr(pos1 + 1, pos2 - pos1 - 1);
		float amount = std::stof(line.substr(pos2 + 1, pos3 - pos2 - 1));
		bool paid = (line.substr(pos3 + 1) == "true");
		bills.emplace_back(company, id, amount, paid);
	}
	file.close();
}

vector<Bill> Repository::getBills() const {
	return bills;
}
