#include "writer.h"

Writer::Writer()
{
	this->name = "";
	this->expertise = "";
}

Writer::Writer(std::string name, std::string expertise)
{
	this->name = name;
	this->expertise = expertise;
}

std::string Writer::getName()
{
	return name;
}

std::string Writer::getExpertise()
{
	return expertise;
}
