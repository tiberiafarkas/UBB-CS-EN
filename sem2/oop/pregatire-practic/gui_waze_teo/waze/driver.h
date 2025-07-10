#pragma once

#include <string>

class Driver
{
private:
	std::string name;
	std::string status;
	int latitude;
	int longitude;
	int score;
public:
	Driver();
	Driver(std::string name, std::string status, int latitude, int longitude, int score);
	std::string getName();
	std::string getStatus();
	int getLatitude();
	int getLongitude();
	int getScore();

	void goNorth();
	void goSouth();
	void goEast();
	void goWest();

	void increaseScore();
	void setStatus();

};