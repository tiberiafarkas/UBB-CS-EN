#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <package.h>

using std::istream;
using std::ostream;
using std::vector;
using std::string;

struct Circle {
	int x;
	int y;
	int radius;
};

class Courier {
private:
	string name;
	vector<string> streets;
	Circle zone;
	vector<Package*> packages;
	bool company;
	bool image;

public:
	Courier() {};
	Courier(string name, vector<string> streets, Circle zone)
		: name(name), streets(streets), zone(zone), company(false), image(false) {
	}
	~Courier() {};
	string getName() { return name; }
	vector<string> getStreets() { return streets; }
	Circle getZone() { return zone; }
	vector<Package*>& getPackages() {
		return packages;
	}
	void setCompany() {
		company = true;
	}
	void setImage() {
		image = true;
	}
	bool isCompany() { return company; }
	void addPackage(Package* p) {
		packages.push_back(p);
	}
	bool isImage() { return image; }
	friend istream& operator>>(istream& is, Courier& courier);
	friend ostream& operator<<(ostream& os, Courier& courier);
};