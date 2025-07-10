#pragma once
#include <string>

using std::string;

class domain {
private:
	string name;
	string date;
	float fee;
	bool active;

public:
	//constructor
	domain();
	domain(const string& name, const string& date, float fee, bool isActive);
	//destructor
	~domain();

	//getters
	string getName();
	string getDate();
	float getFee();
	bool isActive();
};