#include "bill.h"

string Bill::getCompany() {
	return company;
}

string Bill::getId() {
	return id;
}

float Bill::getAmount() {
	return amount;
}

bool Bill::isPaid() {
	return paid;
}