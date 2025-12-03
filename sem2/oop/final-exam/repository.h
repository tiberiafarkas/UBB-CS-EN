#pragma once
#include "volunteer.h"
#include "department.h"

class Repository {
private:
	vector<Volunteer> vol;
	vector<Department> dep;

public:
	Repository();
	void load();
	void save();

	vector<Volunteer>& getVol() {
		return vol;
	}
	vector<Department>& getDep() {
		return dep;
	}
	void addVolunteer(Volunteer& v) {
		vol.push_back(v);
	}
	vector<Volunteer>& getDepVol(Department& d) {
		return d.getVolunteers();
	}
};

