#include "driver.h"

Driver::Driver()
{
	this->name = "";
	this->status = "";
	this->latitude = 0;
	this->longitude = 0;
	this->score = 0;
}

Driver::Driver(std::string name, std::string status, int latitude, int longitude, int score)
{
	this->name = name;
	this->status = status;
	this->latitude = latitude;
	this->longitude = longitude;
	this->score = score;
}

std::string Driver::getName()
{
	return name;
}

std::string Driver::getStatus()
{
	return status;
}

int Driver::getLatitude()
{
	return latitude;
}

int Driver::getLongitude()
{
	return longitude;
}

int Driver::getScore()
{
	return score;
}

void Driver::goNorth()
{
	longitude++;
}

void Driver::goSouth()
{
	longitude--;
}

void Driver::goEast()
{
	latitude++;
}

void Driver::goWest()
{
	latitude--; 
}

void Driver::increaseScore()
{
	score++;
}

void Driver::setStatus()
{
	if(score < 10)
		status = "baby";
	else if (score < 15)
		status = "grown-up";
	else
		status = "knight";
}
