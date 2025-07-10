#pragma once
#include "Biologist.h"
#include "Bacteria.h"
#include <vector>
#include <string>

class Repository {
private:
    std::vector<Biologist> biologists;
    std::vector<Bacteria> bacterias;
    std::string biologistsFileName;
    std::string bacteriasFileName;

public:
    Repository(const std::string& bioFile, const std::string& bactFile) : biologistsFileName(bioFile), bacteriasFileName(bactFile) {
        loadBiologists();
        loadBacterias();
    }
    //destrcutor
    ~Repository();

    void updateBacteria(const Bacteria& bacteria);
    const std::vector<Biologist>& getBiologists() const { return biologists; }
    const std::vector<Bacteria>& getBacterias() const { return bacterias; }
    void loadBiologists();
    void loadBacterias();
    void addBacteria(const Bacteria& bacteria) { bacterias.push_back(bacteria); }
};