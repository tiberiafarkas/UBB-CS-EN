#pragma once

#include <string>

class Report
{
private:
	std::string description;
	std::string reporter;
	int longitude;
	int latitude;
	int validated;
public:
	Report();
	Report(std::string description, std::string reporter, int latitude, int longitude, int validated);
	std::string getDescription();
	std::string getReporter();
	int getLongitude();
	int getLatitude();
	int getValidated();
	void increaseValidated();

	std::string toString();
};