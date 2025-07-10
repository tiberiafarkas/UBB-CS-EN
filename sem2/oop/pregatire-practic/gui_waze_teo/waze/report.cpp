#include "report.h"

Report::Report()
{
	this->description = "";
	this->reporter = "";
	this->longitude = 0;
	this->latitude = 0;
	this->validated = 0;
}

Report::Report(std::string description, std::string reporter, int latitude, int longitude, int validated)
{
	this->description = description; 
	this->reporter = reporter; 
	this->longitude = longitude; 
	this->latitude = latitude; 
	this->validated = validated; 
}

std::string Report::getDescription()
{
	return description;
}

std::string Report::getReporter()
{
	return reporter;
}

int Report::getLongitude()
{
	return longitude;
}

int Report::getLatitude()
{
	return latitude;
}

int Report::getValidated()
{
	return validated;
}

void Report::increaseValidated()
{
	validated++;
}

std::string Report::toString()
{
	if (validated < 2)
		return this->description + " | " + this->reporter + " | " + std::to_string(this->latitude) + " " + std::to_string(this->longitude) + " | false";
	else
		return this->description + " | " + this->reporter + " | " + std::to_string(this->latitude) + " " + std::to_string(this->longitude) + " | true";
}
