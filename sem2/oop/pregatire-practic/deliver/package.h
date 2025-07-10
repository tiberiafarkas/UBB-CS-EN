#pragma once
#include <string>

using std::string;

struct location {
	int x;
	int y;
};

class Package {
private:
	string recipient;
	string address;
	location loc;
	bool delivered = false;

public:
	Package() : delivered(false) {}
	Package(string recipient, string address, int x, int y)
		: recipient(recipient), address(address), loc{ x, y }, delivered(false) {
	}
	string getRecipient() { return recipient; }
	string getAddress() { return address; }
	location getLocation() { return loc; }
	bool isDelivered() { return delivered; }
	void markAsDelivered() { delivered = true; }
	void setUnDelivered() { delivered = false; }
	friend std::istream& operator>>(std::istream& is, Package& package);
	friend std::ostream& operator<<(std::ostream& os, Package& package);
};