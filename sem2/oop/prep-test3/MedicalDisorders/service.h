#pragma once
#include "repository.h"

class Service {
private:
	Repository repo;

public:
	vector<Disorder> getAllDisorders();
	vector<Disorder> getCertainDisorders(string field);
	vector<string> getSymptomps(string name);
};