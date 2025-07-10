#include "DynamicArray.h"
#include "school.h"

School::School() : name(""), longitude(0), latitude(0), date(""), distance(0) {}

School::School(const string& name, float longitude, float latitude, const string& date) {
	this->name = name;
	this->longitude = longitude;
	this->latitude = latitude;
	this->date = date;
	this->distance = 0;
}

School::~School() {

}

string School::getName() {
	return this->name;
}

float School::getLong() {
	return this->longitude;
}

float School::getLat() {
	return this->latitude;
}

string School::getDate() {
	return this->date;
}

float School::getDist() {
	return this->distance;
}

void School::setDist(float d) {
	this->distance = d;
}

