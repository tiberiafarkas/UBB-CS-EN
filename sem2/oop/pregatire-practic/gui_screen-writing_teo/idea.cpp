#include "idea.h"

Idea::Idea()
{
	description = "";
	status = "";
	creator = "";
	act = 0;
}

Idea::Idea(std::string description, std::string status, std::string creator, int act)
{
	this->description = description;
	this->status = status;
	this->creator = creator;
	this->act = act;
}

std::string Idea::getDescription() 
{
	return description;
}

std::string Idea::getStatus() 
{
	return status;
}

std::string Idea::getCreator() 
{
	return creator;
}

int Idea::getAct() 
{
	return act;
}

void Idea::setStatus(std::string newStatus)
{
	status = newStatus; 
}
