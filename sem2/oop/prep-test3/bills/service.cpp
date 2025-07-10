#include "service.h"

vector<Bill> Service::getBills() const {
	return repository.getBills();
}

vector<Bill> Service::getUnpaidBills() const {
	vector<Bill> unpaidBills;
	for (auto bill : repository.getBills()) {
		if (!bill.isPaid()) {
			unpaidBills.push_back(bill);
		}
	}
	return unpaidBills;
}

vector<Bill> Service::getPaidBills() const {
	vector<Bill> paidBills;
	for (auto bill : repository.getBills()) {
		if (bill.isPaid()) {
			paidBills.push_back(bill);
		}
	}
	return paidBills;
}

float Service::unpaidAmount(string company) const {
	float total = 0;
	bool found = 0;
	for (auto bill : this->getUnpaidBills()) {
		if (bill.getCompany() == company) {
			found = 1;
			if (bill.isPaid() == false) {
				total += bill.getAmount();
			}
		}
	}
	if (!found) {
		throw std::exception("No company named this way!");
	}

	return total;
}