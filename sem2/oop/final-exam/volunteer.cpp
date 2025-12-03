#include "volunteer.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using std::string, std::vector, std::istream, std::ostream, std::stringstream;

istream& operator>>(istream& is, Volunteer& v) {
    string line;
    if (!getline(is, line))
        return is;

    stringstream ss(line);
    string skillsStr;

    string name, email, department;

    getline(ss, name, '|');
    getline(ss, email, '|');
    getline(ss, skillsStr, '|');
    getline(ss, department);

    v.setName(name);
	v.setEmail(email);
	v.setDepartment(department);

    vector<string> skills;
    std::stringstream skillsStream(skillsStr);
    std::string skill;
    while (std::getline(skillsStream, skill, ',')) {
        skills.push_back(skill);
    }
    v.setListOfInterests(skills);

    return is;
}
ostream& operator<<(ostream& os, Volunteer v) {

	os << v.getName() << "|" << v.getEmail() << "|";
	for (auto& interest : v.getListOfInterests()) {
		os << interest << ",";
	}
	os << "|" << v.getDepartment();
	return os;
}