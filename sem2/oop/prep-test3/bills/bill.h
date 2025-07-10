#pragma once
#include <string>

using std::string;

class Bill {
private:
	string company;
	string id;
	float amount;
	bool paid;

public:
	Bill(const string& company, const string& id, float amount, bool paid = false) : company(company), id(id), amount(amount), paid(paid) {}
	~Bill() {}
	string getCompany();
	string getId();
	float getAmount();
	bool isPaid();
	string toString() {
		return "Company: " + company + " |  Amount: " + std::to_string(amount);
	}
};