#pragma once
#include <string>

struct Location {
	int x;
	int y;
};

class Package
{
private:
	std::string recipient;
	std::string address;
	Location location;
	bool status;
public:
	Package(const std::string& recipient, const std::string& address, const Location& location, const bool status) : recipient{ recipient }, address{ address }, location{ location }, status{ status } {};
	std::string getRecipient() const { return this->recipient; };
	std::string getAddress() const { return this->address; };
	Location getLocation() const { return this->location; };
	bool getStatus() const { return this->status; };
	void setStatus(bool status) { this->status = status; };
	std::string toString() const {
		return this->getRecipient() + " - " + this->getAddress();
	 };
};

