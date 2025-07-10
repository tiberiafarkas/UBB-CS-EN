#pragma once
#include<string>
#include<iostream>
#include<vector>

using namespace std;

class Biologist {
private:
	string name;
	vector<string> studiedSpecies;
public:
	Biologist(string name = "", vector<string> studiedSpecies = {}) :
		name{ name }, studiedSpecies{ studiedSpecies } {};
	string getName() const { return name; }
	vector<string> getStudiedSpecies() const { return studiedSpecies; }
};