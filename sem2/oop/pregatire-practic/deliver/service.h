#pragma once
#include "repository.h"
#include "observer.h"

class Service : public Subject {
private:
	Repository repo;

public:
	vector<Courier>& getCuriers() {
		return repo.getCouriers();
	}
	vector<Package>& getPackages() {
		return repo.getPackages();
	}
	vector<Package> getUnDeliveredPackages(Courier& c) {
		return repo.getUnDeliveredPackages(c);
	}
	vector<Package> getPackagesByStreet(Courier c, string street) {
		vector<Package*> packages = c.getPackages();
		vector<Package> filteredPackages;
		for (auto package : packages) {
			if (package->getAddress().find(street) != string::npos) {
				filteredPackages.push_back(*package);
			}
		}
	}
	void addPackage(Package p) {
		repo.addPackage(p);
	}
	void deliverPackage(const std::string& recipient, const std::string& address) {
		repo.markPackageAsDelivered(recipient, address);
	}
};