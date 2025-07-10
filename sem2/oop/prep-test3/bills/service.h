#pragma once
#include "repository.h"

class Service {
private:
	Repository repository;

public:
	vector<Bill> getBills() const;
	vector<Bill> getUnpaidBills() const;
	vector<Bill> getPaidBills() const;
	float unpaidAmount(string company) const;
};