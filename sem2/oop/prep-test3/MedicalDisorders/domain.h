#pragma once
#include <string>

using std::string;

class Disorder{
private:
	string category, name, symptomps;

public:
	Disorder(string category, string name, string symptomps) : category{ category }, name{ name }, symptomps{ symptomps } {};
	~Disorder() {};
	string getCategory();
	string getName();
	string getSymptomps();
	string toString() {
		return this->category +" " + this->name;
	}
};