//
// Created by Dragos on 6/30/2022.
//

#include "SRepo.h"

SRepo::SRepo() {
    read_from_file();
}

SRepo::~SRepo() {
    save_to_file();
}

#include <fstream>

void SRepo::read_from_file() {
    std::ifstream f(file_name);
    while(!f.eof()){
        Source_File q;
        f>> q;
        if(q.getName().empty())
            break;
        this->source_files.push_back(q);
    }
    f.close();

}

void SRepo::save_to_file() {
    std::ofstream f(file_name);
    f.clear();
    for(const auto& q:source_files){
        f<<q<<"\n";
    }
    f.close();
}

vector<Source_File>& SRepo::getAll() {
    return source_files;
}

void SRepo::add_sf(Source_File &sf) {
    source_files.push_back(sf);
}
