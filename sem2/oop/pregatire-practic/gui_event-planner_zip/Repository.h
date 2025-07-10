#pragma once

#include <vector>
#include "Person.h"
#include "Event.h"

using namespace std;

class Repository {

private:
    vector<Person> arrpers;
    vector<Event> arreven;

public:
    Repository();

    vector<string >split(string line, char delim);

    void readFromFilePers();
    void readFromFileEvent();

    void saveToFilePers();
    void saveToFileEvent();

    vector<Event> &getEvents();
    vector<Person> &getPersons();

    vector<Event> getEventByOrganiser(string name);
    vector<Event> getTheClosestEvents(Person pers);

    int addEvent(Event &even);
    //int addParticipant(Event even, Person pers);

    void updateDateOfEvent(Event ev,int newDate);
    void updateDescrOfEvent(Event ev, string descr);

    vector<Event> getMostPopulars();

    Event &getEvent(string name, int longg, int lat);

};
