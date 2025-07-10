//
// Created by Dragos on 6/30/2022.
//

#include "Source_File.h"

Source_File::Source_File(const string &name, const string &status, const string &creator, const string &reviewer)
        : name(name), status(status), creator(creator), reviewer(reviewer) {}

Source_File::Source_File() {
    name = "";
    status = "not revised";
    creator = "";
    reviewer = "";
}

Source_File::~Source_File() {

}

const string &Source_File::getName() const {
    return name;
}

void Source_File::setName(const string &name) {
    Source_File::name = name;
}

const string &Source_File::getStatus() const {
    return status;
}

void Source_File::setStatus(const string &status) {
    Source_File::status = status;
}

const string &Source_File::getCreator() const {
    return creator;
}

void Source_File::setCreator(const string &creator) {
    Source_File::creator = creator;
}

const string &Source_File::getReviewer() const {
    return reviewer;
}

void Source_File::setReviewer(const string &reviewer) {
    Source_File::reviewer = reviewer;
}

ostream &operator<<(ostream &os, const Source_File &file) {
    os <<  file.name << "," << file.status << "," << file.creator << "," << file.reviewer;
    return os;
}

vector<string> tokenize(std::string str, char delimiter)
{
    std::vector <std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::istream &operator>>(std::istream &is, Source_File &sf){
    std::string line;
    getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 4)
        return is;
    sf.setName(tokens[0]);
    sf.setStatus(tokens[1]);
    sf.setCreator(tokens[2]);
    sf.setReviewer(tokens[3]);
    return is;
}

bool Source_File::is_revised() {
    return status == "revised";
}