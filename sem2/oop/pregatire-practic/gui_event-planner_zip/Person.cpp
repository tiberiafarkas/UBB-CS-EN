//
// Created by teodo on 6/20/2024.
//

#include "Person.h"

Person::Person(string name, float latitude, float longitude, bool status) {
    this->name=name;
    this->longitude=longitude;
    this->latitude=latitude;
    this->status=status;

}

Person::Person() = default;

string Person::getName() {
    return this->name;
}

float Person::getLatitude() {
    return this->latitude;
}

float Person::getLongitude() {
    return this->longitude;
}

bool Person::getStatus() {
    return this->status;
}
