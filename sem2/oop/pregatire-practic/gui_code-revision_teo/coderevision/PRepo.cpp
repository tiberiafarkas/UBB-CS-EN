//
// Created by Dragos on 6/30/2022.
//

#include "PRepo.h"

PRepo::PRepo() {
    read_from_file();
}

PRepo::~PRepo() {
    save_to_file();
}

#include <fstream>

void PRepo::read_from_file() {
    std::ifstream f(file_name);
    while(!f.eof()){
        Programmer q;
        f>> q;
        if(q.getName().empty())
            break;
        this->programmers.push_back(q);
    }
    f.close();
}

void PRepo::save_to_file() {
    std::ofstream f(file_name);
    f.clear();
    for(const auto& q:programmers){
        f<<q<<"\n";
    }
    f.close();
}

vector<Programmer> &PRepo::getAll() {
    return programmers;
}
