#include "repository.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <qdebug.h>

Repository::Repository()
{
	readWritersFromFile();
	readIdeasFromFile();
}

Repository::~Repository()
{
}

void Repository::addIdea(Idea idea)
{
	if(idea.getDescription() == "")
		throw std::exception("Description cannot be empty!");
	if (idea.getAct() < 1 || idea.getAct() > 3)
		throw std::exception("Act must be between 1 and 3!");
	for(auto i : ideas)
		if (i.getDescription() == idea.getDescription() && i.getAct() == idea.getAct())
			throw std::exception("Idea already exists!");
	ideas.push_back(idea);
}

std::vector<Idea>& Repository::getIdeas()
{
	std::sort(ideas.begin(), ideas.end(), [](Idea a, Idea b) {return a.getAct() < b.getAct(); }); 
	return ideas;
}

std::vector<Writer>& Repository::getWriters()
{
	return writers;
}

void Repository::readWritersFromFile()
{
	std::ifstream file("../w.txt");
	std::string line; 
	while (getline(file, line))
	{
		std::stringstream ss(line); 
		std::string name, expertise; 
		ss >> name >> expertise; 
		writers.push_back(Writer(name, expertise)); 
	}
	file.close(); 
}

void Repository::readIdeasFromFile()
{
	std::ifstream file("../i.txt"); 
	std::string line; 
	while (getline(file, line)) 
	{
		std::stringstream ss(line); 
		std::string description, status, creator;
		int act;
		ss >> description >> status >> creator >> act; 
		ideas.push_back(Idea{ description, status, creator, act });  
	} 
	file.close(); 
}
