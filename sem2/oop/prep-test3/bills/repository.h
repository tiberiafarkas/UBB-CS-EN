#pragma once
#include "bill.h"
#include <vector>

using std::vector;

class Repository {
private:
	vector<Bill> bills;

public:
	Repository() {
		this->load();
	}
	void load();
	vector<Bill> getBills() const;
};