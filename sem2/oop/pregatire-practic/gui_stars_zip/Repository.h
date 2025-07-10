#pragma once
#include<iostream>
#include "Star.h"
#include "Astronaut.h"
#include<vector>
#include<set>
#include<string>
#include<fstream>

class Repository
{
private:
	vector<Astronaut> astronauts;
	vector<Star> stars;
	string astronautsFileName, starsFileName;

public:
	Repository(string astronautsFileName, string starsFileName) : astronautsFileName{ astronautsFileName }, starsFileName{ starsFileName }
	{
		loadStars();
		loadAstronauts();
	}
	~Repository();
	void loadAstronauts();
	void loadStars();
	void addStar(const Star& star) { stars.push_back(star); }
	vector<Astronaut> &getAstronauts() { return astronauts; }
	vector<Star> &getStars() { return stars; }

};

