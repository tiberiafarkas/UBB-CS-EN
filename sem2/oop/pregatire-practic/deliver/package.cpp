#include "package.h"
#include <sstream>
#include <iostream>

using std::istream, std::stringstream, std::ostream;

istream& operator>>(istream& is, Package& package) {
	string line;
	if (getline(is, line)) {
		stringstream ss(line);
		string recipient, address;
		getline(ss, recipient, '|');
		package.recipient = recipient;
		getline(ss, address, '|');
		package.address = address;

		string x, y;
		if (getline(ss, x, ',') && getline(ss, y)) {
			package.loc.x = std::stoi(x);
			package.loc.y = std::stoi(y);
		}
	}
	return is;
}

ostream& operator<<(ostream& os, Package& package) {
	os << package.recipient << '|' << package.address << '|' << package.loc.x << ',' << package.loc.y;
	return os;
}