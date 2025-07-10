#pragma once
#include "repository.h"

class Service {
private:
    Repository repository;
public:
    Service() = default;
    vector<Ideea>& getIdeas();
    vector <Researcher>& getResearchers() { return this->repository.getResearchers(); }
    void addIdeea(Ideea idea) { this->repository.addIdeea(idea); }
    void saveAllToFile() { this->repository.saveAllToFile(); }
    void saveIdeeaToFile(Ideea idea) { this->repository.saveIdeeaToFile(idea); }
};