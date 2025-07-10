#pragma once
#include "DynamicArray.h"
#include <string>

using std::string;

class School {
private:
	string name;
	float longitude, latitude, distance;
	string date;

public:
	School();
	School(const string& name, float longitude, float latitude, const string& date);
	~School();

	string getName();
	float getLat();
	float getLong();
	string getDate();
	float getDist();
	void setDist(float d);
};

