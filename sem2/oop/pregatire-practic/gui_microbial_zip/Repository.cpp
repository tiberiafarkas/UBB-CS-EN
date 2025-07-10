#include "Repository.h"
#include <fstream>
#include <sstream>
#include<algorithm>

void Repository::loadBiologists() {
    std::ifstream input(this->biologistsFileName);
    const char sep = '|';
    std::string line;
    std::string name, studiedSpeciesString;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        std::getline(iss, name, sep);
        std::getline(iss, studiedSpeciesString, sep);

        std::vector<std::string> studiedSpecies;
        std::istringstream speciesStream(studiedSpeciesString);
        std::string species;
        while (std::getline(speciesStream, species, ',')) {
            studiedSpecies.push_back(species);
        }

        this->biologists.emplace_back(name, studiedSpecies);
    }
}

void Repository::loadBacterias() {
    std::ifstream inputFile(this->bacteriasFileName);
    const char sep = '|';
    std::string line;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string name, species, sizeStr, diseasesStr;
        std::vector<std::string> causedDiseases;

        std::getline(iss, name, sep);
        std::getline(iss, species, sep);
        std::getline(iss, sizeStr, sep);
        std::getline(iss, diseasesStr, sep);

        int size = std::stoi(sizeStr);

        std::istringstream diseasesStream(diseasesStr);
        std::string disease;
        while (std::getline(diseasesStream, disease, ',')) {
            causedDiseases.push_back(disease);
        }

        Bacteria bacteria(name, species, size, causedDiseases);
        this->bacterias.push_back(bacteria);
    }
    sort(bacterias.begin(), bacterias.end());
}

Repository::~Repository() {
    std::ofstream fout(bacteriasFileName);
    size_t numBacterias = bacterias.size();
    for (size_t i = 0; i < numBacterias; ++i) {
        const auto& bacteria = bacterias[i];
        fout << bacteria.getName() << '|' << bacteria.getSpecies() << '|' << bacteria.getSize() << "|";

        const auto& diseases = bacteria.getcausedDiseases();
        for (size_t j = 0; j < diseases.size(); ++j) {
            fout << diseases[j];
            if (j < diseases.size() - 1) {
                fout << ',';
            }
        }

        // Add a newline only if this is not the last bacterium
        if (i < numBacterias - 1) {
            fout << '\n';
        }
    }
    fout.close();
}



void Repository::updateBacteria(const Bacteria& updatedBacteria) {
    auto it = std::find_if(bacterias.begin(), bacterias.end(), [&updatedBacteria](const Bacteria& b) {
        return b.getName() == updatedBacteria.getName(); // Assuming name is unique
        });
    if (it != bacterias.end()) {
        *it = updatedBacteria;
    }
}