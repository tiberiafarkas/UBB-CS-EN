#include "repository.h"
#include <fstream>

using std::ifstream, std::ofstream;

Repository::Repository() {
	load();
}

void Repository::load() {
	ifstream fin("volunteers.txt");
	if (!fin.is_open()) {
		throw std::runtime_error("Could not open volunteers.txt");
	}
	Volunteer v;
	while (fin >> v) {
		vol.push_back(v);
	}
	fin.close();
	ifstream finDep("departments.txt");
	if (!finDep.is_open()) {
		throw std::runtime_error("Could not open departments.txt");
	}
	Department d;
	while (finDep >> d) {
		dep.push_back(d);
	}
	finDep.close();
}

void Repository::save() {
	ofstream fout("volunteers.txt");
	if (!fout.is_open()) {
		throw std::runtime_error("Could not open volunteers.txt for writing");
	}
	for (auto& v : vol) {
		fout << v << "\n";
	}
}