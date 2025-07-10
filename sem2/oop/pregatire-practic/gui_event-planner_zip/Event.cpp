//
// Created by teodo on 6/20/2024.
//

#include "Event.h"

Event::Event(string organiser, string name, string description, float latitude, float longitude, int date, vector<Person> participants) {
    this->organiser=organiser;
    this->name=name;
    this->description=description;
    this->latitude=latitude;
    this->longitude=longitude;
    this->date=date;
    this->participants=participants;

}

string Event::getOrganiser() {
    return this->organiser;
}

string Event::getName() {
    return this->name;
}

string Event::getDescription() {
    return this->description;
}

float Event::getLatitude() {
    return this->latitude;
}

float Event::getLongitude() {
    return this->longitude;
}

int Event::getDate() {
    return this->date;
}

vector<Person> Event::getParticipants() {
    return this->participants;
}

void Event::setParticipants(vector<Person> list) {
    this->participants=list;

}

void Event::setDescription(string descr) {
    this->description=descr;

}

void Event::setDate(int newDate) {
    this->date=newDate;

}

Event::Event() = default;
