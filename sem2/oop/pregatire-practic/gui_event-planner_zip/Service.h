#pragma once
#include "Repository.h"
#include "Observer.h"

class Service : public Subject {

private:
    Repository repo;

public:
    Service();

    void readFromFilePers();
    void readFromFileEvent();

    void saveToFilePers();
    void saveToFileEvent();

    vector<Event> &getEvents();
    vector<Person> &getPersons();

    vector<Event> getEventByOrganiser(string name);
    vector<Event> getTheClosestEvents(Person pers);

    int addEvent(Event &even);
    int addParticipant(Event& even, Person& pers);

    void updateDateOfEvent(Event ev,int newDate);
    void updateDescrOfEvent(Event ev, string descr);

    vector<Event> getMostPopulars();

    Event &getEvent(string name, int longg, int lat);
};

