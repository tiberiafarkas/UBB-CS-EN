#pragma once

#include <string>
#include <vector>
#include "Person.h"

using namespace std;

class Event {

private:
    string organiser,name,description;
    float latitude, longitude;
    int date;
    vector<Person> participants;

public:
    Event(string organiser, string name, string description,float latitude,float longitude, int date, vector<Person> participants);
    Event();

    string getOrganiser();
    string getName();
    string getDescription();
    float getLatitude();
    float getLongitude();
    int getDate();
    vector<Person> getParticipants();
    void setParticipants(vector<Person> list);
    void setDescription(string descr);
    void setDate(int newDate);


};
