#include "Repository.h"

bool Repository::add(School s) {
	for (int i = 0; i < this->schools.getSize(); ++i) {
		if (this->schools[i].getName() == s.getName() && this->schools[i].getLat() == s.getLat() && this->schools[i].getLong() == s.getLong()) {
			return false;
		}
	}
	this->schools.add(s);
	return true;
}

DynamicArray<School> Repository::getAll() {
	return this->schools;
}