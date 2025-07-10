//
// Created by teodo on 6/20/2024.
//

#include <sstream>
#include <fstream>
#include "Repository.h"

Repository::Repository():arreven(0) , arrpers(0){

}

vector<string >Repository::split(string line, char delim) {
    vector<string> tokens;
    stringstream ss{line};
    string current;
    while (getline(ss, current, delim))
    {
        tokens.push_back(current);
    }
    return tokens;

}

void Repository::readFromFilePers() {
    ifstream file("persons.txt");
    if(!file.is_open())
        throw exception();

    string line;
    while(getline(file, line))
    {
        vector <string> items;
        items = split(line, ',');
        Person pers = Person(items[0], stoi(items[1]), stoi(items[2]), (bool)stoi(items[3]));
        arrpers.push_back(pers);

    }
    file.close();

}

void Repository::readFromFileEvent() {
    ifstream file("events.txt");
    if(!file.is_open())
        throw exception();

    string line;
    while(getline(file, line))
    {
        vector <string> items;
        items = split(line, ',');
        vector<Person> part;
        Event even = Event(items[0], items[1], items[2], stoi(items[3]), stoi(items[4]), stoi(items[5]),part);
        arreven.push_back(even);

    }
    file.close();

}

void Repository::saveToFilePers() {
    ofstream g("persons.txt");
    for(auto i:arrpers) {
        g << i.getName() << "," << i.getLatitude() << "," << i.getLongitude()<<","<<i.getStatus()<<'\n';
    }
    g.close();

}

void Repository::saveToFileEvent() {
    ofstream g("events.txt");
    for(auto i:arreven) {
        g <<i.getOrganiser()<<","<<i.getName() << ","<<i.getDescription()<<","<< i.getLatitude() << "," << i.getLongitude()<<","<<i.getDate()<<'\n';
    }
    g.close();

}

vector<Event> &Repository::getEvents() {
    return arreven;
}

vector<Person> &Repository::getPersons() {
    return arrpers;
}

vector<Event> Repository::getEventByOrganiser(string name) {
    vector<Event> arr;
    for(auto i:arreven)
    {
        if(i.getName() == name)
            arr.push_back(i);
    }
    return arr;
}

vector<Event> Repository::getTheClosestEvents(Person pers) {
    vector<Event> arr;
    for(auto i:arreven)
    {
        if(abs(i.getLongitude()-pers.getLongitude())+ abs(i.getLatitude()-pers.getLatitude()) <= 5)
            arr.push_back(i);
    }
    return arr;
}

int Repository::addEvent(Event &even) {
    for(auto i:arreven)
    {
        if(i.getName() == even.getName() && i.getLatitude() == even.getLatitude() && i.getLongitude()==even.getLongitude())
            return -1;
    }
    arreven.push_back(even);
    saveToFileEvent();
    saveToFileEvent();
    return 1;
}

/*
int Repository::addParticipant(Event even, Person pers) {
    if(!even.getParticipants().empty())
        for(auto &&i:even.getParticipants())
        {
            if(i.getName() == pers.getName())
                return -1;
        }
    vector<Person> arr = even.getParticipants();
    arr.push_back(pers);
    even.setParticipants(arr);
    return 1;

}*/

void Repository::updateDateOfEvent(Event ev,int newDate) {
    ev.setDate(newDate);

}

void Repository::updateDescrOfEvent(Event ev, string descr) {
    ev.setDescription(descr);

}

vector<Event> Repository::getMostPopulars() {
    return arreven;
}

Event &Repository::getEvent(string name, int longg, int lat) {
    for (auto &&i: arreven)
    {
        if(i.getName() == name && i.getLongitude() == longg && i.getLatitude() == lat)
            return i;
    }
}
