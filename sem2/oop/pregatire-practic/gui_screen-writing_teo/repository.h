#pragma once

#include <vector>
#include "idea.h"
#include "writer.h"

class Repository
{
private:
	std::vector<Idea> ideas;
	std::vector<Writer> writers;
public:
	Repository();
	~Repository();
	void addIdea(Idea idea);
	std::vector<Idea>& getIdeas();
	std::vector<Writer>& getWriters();

	void readWritersFromFile();
	void readIdeasFromFile();
};