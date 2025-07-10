#include "Service.h"
#include <sstream>

std::vector<Bacteria> Service::getBacteriasFileterd(const std::string& name) {
    std::vector<Bacteria> bacterias = repository.getBacterias(), filtered;
    for (auto& b : bacterias) {
        if (b.getName() == name) filtered.push_back(b);
    }
    return filtered;
}

std::vector<std::string> splitDiseases(const std::string& diseasesString) {
    std::vector<std::string> diseases;
    std::istringstream stream(diseasesString);
    std::string disease;

    while (std::getline(stream, disease, ',')) {
        diseases.push_back(disease);
    }

    return diseases;
}

bool find_with_same_name(const Bacteria& bacteria, const std::vector<Bacteria>& bacterias) {
    for (const auto& b : bacterias) {
        if (b.getName() == bacteria.getName() || b.getSpecies() == bacteria.getSpecies()) {
            return true;
        }
    }
    return false;
}

void Service::addBacteria(const std::string& name, const std::string& species, int size, const std::string& causedDiseasesString) {
    std::vector<std::string> causedDiseases = splitDiseases(causedDiseasesString);
    Bacteria bacteria{ name, species, size, causedDiseases };
    if (find_with_same_name(bacteria, getBacterias())) throw std::runtime_error("Same name or species!");
    repository.addBacteria(bacteria);
}