#include "domain.h"
#include <string>

using std::string;

domain::domain() : name(""), date(""), fee(0), active(false) {}

domain::domain(const string& name, const string& date, float fee, bool active)
{
	this->name = name;
	this->date = date;
	this->fee = fee;
	this->active = active;
}

domain::~domain() {}

string domain::getName()
{
	return this->name;
}

string domain::getDate()
{
	return this->date;
}

float domain::getFee()
{
	return this->fee;
}

bool domain::isActive()
{
	return this->active;
}