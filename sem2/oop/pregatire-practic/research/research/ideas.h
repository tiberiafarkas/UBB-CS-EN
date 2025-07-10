#pragma once
using namespace std;
#include "string"

class Ideea {
private:
    string title, description, status;
    string creator;
    int duration;
public:
    Ideea() = default;
    Ideea(string title, string description, string status, string researcher, int duration) {
        this->title = title;
        this->description = description;
        this->status = status;
        this->duration = duration;
        this->creator = researcher;
    }
    string getTitle() const { return this->title; }
    string getDescription() const { return this->description; }
    string getStatuts() const { return  this->status; }
    string getCreator() const { return this->creator; }
    void setStatus(string status) { this->status = status; }
    int getDuration() const { return this->duration; }
    void setDescription(string description) { this->description = description; }

    friend istream& operator>>(istream& in, Ideea& ideea);
    friend ostream& operator<<(ostream& out, Ideea ideea);
};
