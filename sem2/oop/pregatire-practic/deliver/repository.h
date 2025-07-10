#pragma once
#include "courier.h"
#include "package.h"
#include <vector>

using std::vector;

class Repository {
private:
	vector<Courier> couriers;
	vector<Package> packages;

public:
	Repository() {
		load();
	}
	~Repository() {}
	void load();
	void saveToFile();
	vector<Courier>& getCouriers() {
		return couriers;
	}
	vector<Package>& getPackages() {
		return packages;
	}
	vector<Package> getUnDeliveredPackages(Courier& courier) {
		vector<Package> result;
		for (auto& package : getPackages()) {
			if (package.isDelivered())
				continue;

			for (auto& street : courier.getStreets()) {
				if (package.getAddress().find(street) != std::string::npos) {
					result.push_back(package);
					break;
				}
			}
		}
		return result;
	}
	void markPackageAsDelivered(const std::string& recipient, const std::string& address) {
		for (auto& p : packages) {
			if (p.getRecipient() == recipient && p.getAddress() == address) {
				p.markAsDelivered();
				saveToFile();
				break;
			}
		}
	}
	void addPackage(Package p) {
		packages.push_back(p);
		saveToFile();
	}
};