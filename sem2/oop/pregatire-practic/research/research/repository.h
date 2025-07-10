#pragma once
#include "researcher.h"
#include "ideas.h"

class Repository {
private:
    vector<Ideea> ideas;
    vector<Researcher> researchers;
    void readFromFile();
public:
    void saveAllToFile();
    void saveIdeeaToFile(Ideea idea);
    Repository() { readFromFile(); }
    vector<Ideea>& getIdeas() { return this->ideas; }
    vector <Researcher>& getResearchers() { return this->researchers; }
    void addIdeea(Ideea idea) { this->ideas.push_back(idea); }
};