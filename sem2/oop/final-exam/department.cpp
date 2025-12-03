#include "department.h"
#include <sstream>
#include <iostream>

using std::string, std::istream, std::ostream, std::stringstream;

istream& operator>>(istream& is, Department& d) {
	string name, description;
	getline(is, name, '|');
	getline(is, description);
	d.setName(name);
	d.setDescription(description);
	return is;
}

