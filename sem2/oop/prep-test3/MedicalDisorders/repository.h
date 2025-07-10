#pragma once
#include <vector>
#include <fstream>
#include "domain.h"

using std::vector;

class Repository {
private:
	vector<Disorder> disorders;

public:
	Repository() {
		this->load();
	}
	void load();
	vector<Disorder> getAllDisorders();
	~Repository() {};
};
