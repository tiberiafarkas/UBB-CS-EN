//
// Created by teodo on 6/20/2024.
//

#include <algorithm>
#include "Service.h"

Service::Service() : repo(){

}

void Service::readFromFilePers() {
    repo.readFromFilePers();

}

void Service::readFromFileEvent() {
    repo.readFromFileEvent();

}

void Service::saveToFilePers() {
    repo.saveToFilePers();

}

void Service::saveToFileEvent() {
    repo.readFromFileEvent();

}

bool compare2(Event a, Event b)
{
    return a.getDate()<b.getDate();
}

vector<Event> &Service::getEvents() {
    vector<Event>&arr2= repo.getEvents();
    sort(arr2.begin(), arr2.end(), compare2);
    return arr2;
}

vector<Person> &Service::getPersons() {
    return repo.getPersons();
}

vector<Event> Service::getEventByOrganiser(string name) {
    return repo.getEventByOrganiser(name);
}

vector<Event> Service::getTheClosestEvents(Person pers) {
    return repo.getTheClosestEvents(pers);
}

int Service::addEvent(Event &even) {
    return repo.addEvent(even);

}

int Service::addParticipant(Event& even, Person& pers) {
    for(auto &&i:even.getParticipants())
    {
        if(i.getName() == pers.getName())
            return -1;
    }
    vector<Person> arr = even.getParticipants();
    arr.push_back(pers);
    even.setParticipants(arr);
    return 1;
}

void Service::updateDateOfEvent(Event ev, int newDate) {
    repo.updateDateOfEvent(ev, newDate);
    repo.saveToFileEvent();
    repo.saveToFileEvent();

}

void Service::updateDescrOfEvent(Event ev, string descr) {
    repo.updateDescrOfEvent(ev, descr);
    repo.saveToFileEvent();
    repo.saveToFileEvent();

}

bool compare(Event a, Event b)
{
    return a.getParticipants().size() > b.getParticipants().size();
}

vector<Event> Service::getMostPopulars() {
    vector<Event> arr = repo.getMostPopulars();
    sort(arr.begin(), arr.end(), compare);
    return arr;
}

Event &Service::getEvent(string name, int longg, int lat) {
    return repo.getEvent(name, longg, lat);
}
