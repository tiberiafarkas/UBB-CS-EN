#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<string>

using namespace std;


class Bacteria {
private:
	string name, species;
	int size;
	vector<string> causedDiseases;

public:
	Bacteria(string name = "", string species = "", int size = 0,
		vector<string> causedDiseases = {}) : name{ name }, species{ species },
		size{ size }, causedDiseases{ causedDiseases } {};
	string getName() const { return name; }
	string getSpecies() const { return species; }
	int getSize() const { return size; }
	vector<string> getcausedDiseases() const { return causedDiseases; }
	bool operator<(const Bacteria& other) { return name < other.name; }
	void setName(const std::string& name) {
		this->name = name;
	}

	void setSpecies(const std::string& species) {
		this->species = species;
	}

	void setSize(int size) {
		this->size = size;
	}

	void setCausedDiseases(const std::vector<std::string>& causedDiseases) {
		this->causedDiseases = causedDiseases;
	}
};