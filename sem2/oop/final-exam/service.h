#pragma once
#include "repository.h"
#include "observer.h"

class Service : public Subject {
private:
	Repository repo;
public:
	void addVolunteer(Volunteer& v);

	void save() {
		repo.save();
	}

	vector<Volunteer>& getVolunteers() {
		return repo.getVol();
	}
	vector<Department>& getDepartments() {
		return repo.getDep();
	}
	vector<Volunteer>& getDepartmentVolunteers(Department& d) {
		return repo.getDepVol(d);
	}

	void updateVolunteer(Volunteer& v) {
		for (auto& volunteer : repo.getVol()) {
			if (volunteer.getName() == v.getName()) {
				volunteer = v;
				notifyAllObservers();
				return;
			}
		}
	}
};
