#include "Service.h"
#include <cmath>
#include <algorithm>

bool Service::add(School s) {
	return this->repo.add(s);
}

DynamicArray<School> Service::getAll() {
	return this->repo.getAll();
}

DynamicArray<School> Service::getSchoolsSortedByDistanceandName(float lat, float longit) {
	DynamicArray<School> schools = this->repo.getAll();

	for (int i = 0; i < schools.getSize(); ++i) {
		School x = schools[i];
		float x1 = x.getLong();
		float x2 = longit;
		float y1 = x.getLat();
		float y2 = lat;

		float distance = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		schools[i].setDist(distance);
	}

	for (int i = 0; i < schools.getSize(); ++i) {
		for (int j = i + 1; j < schools.getSize(); ++j) {
			if (schools[i].getDist() > schools[j].getDist() || schools[i].getDist() == schools[j].getDist() && schools[i].getName() > schools[j].getName()) {
				School aux = schools[i];
				schools[i] = schools[j];
				schools[j] = aux;
			}
		}
	}

	DynamicArray<School> sorted_sc;
	int lim = schools.getSize() - 1;
	if (3 < schools.getSize() - 1)
		lim = 2;

	for (int i = 0; i < lim; ++i) {
		sorted_sc.add(schools[i]);
	}

	return sorted_sc;
}