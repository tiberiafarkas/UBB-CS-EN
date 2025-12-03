#pragma once
#include <string>
#include <vector>
#include <iostream>

using std::string, std::vector, std::ostream, std::istream;

class Volunteer {
private:
	string name, email;
	vector<string> listOfInterests;
	string dep;
	double score;

public:
	Volunteer() {};
	Volunteer(string name, string email, vector<string> listOfInterest, string dep) :
		name(name), email(email), listOfInterests(listOfInterest), dep(dep) {
	}
	~Volunteer() = default;

	string getName() { return name; }
	string getEmail() { return email; }
	vector<string> getListOfInterests() { return listOfInterests; }
	string getDepartment() { return dep; }
	double getScore() { return score; }

	void setName(string& name) { this->name = name; }
	void setEmail(string& email) { this->email = email; }
	void setListOfInterests(vector<string>& listOfInterests) {
		this->listOfInterests = listOfInterests;
	}
	void setDepartment(string& dep) { this->dep = dep; }
	void setScore(double score) { this->score = score; }

	friend istream& operator>>(istream& is, Volunteer& v);
	friend ostream& operator<<(ostream& os, Volunteer v);
};