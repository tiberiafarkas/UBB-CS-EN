#pragma once
#include <string>
#include <iostream>
#include <volunteer.h>

using std::string, std::istream;

class Department {
private:
	string name;
	string description;
	vector<Volunteer> volunteers;
	bool mainWindow;

public:
	Department() {};
	Department(string name, string description) : name(name), description(description), mainWindow(false) {}
	~Department() {}

	string getName() { return name; }
	string getDescription() { return description; }
	void setName(string& name) { this->name = name; }
	void setDescription(string& description) { this->description = description; }
	void setMainWindow(bool mainWindow) { this->mainWindow = mainWindow; }
	bool isMainWindow() { return mainWindow; }

	vector<Volunteer>& getVolunteers() { return volunteers; }

	friend istream& operator>>(istream& is, Department& d);
};