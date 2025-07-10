#pragma once
#include "Repository.h"
#include <vector>
#include <string>

class Service {
private:
    Repository& repository;

public:
    Service(Repository& repository) : repository(repository) {}
    std::vector<Biologist> getBiologists() { return repository.getBiologists(); }
    std::vector<Bacteria> getBacterias() { return repository.getBacterias(); }
    std::vector<Bacteria> getBacteriasFileterd(const std::string& name);
    void addBacteria(const std::string& name, const std::string& species, int size, const std::string& causedDiseasesString);
};