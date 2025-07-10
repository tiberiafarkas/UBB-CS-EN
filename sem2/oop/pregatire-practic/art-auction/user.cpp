#include "user.h"
#include <sstream>

//the fields are separated by | in file
istream& operator>>(istream& is, User& u) {
	string line;
	if (getline(is, line)) {
		std::stringstream ss(line);
		getline(ss, u.name, '|');
		getline(ss, u.type, '|');
		ss >> u.id;
	}
	return is;
}