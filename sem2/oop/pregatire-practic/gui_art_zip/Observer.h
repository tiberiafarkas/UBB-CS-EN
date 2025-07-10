#pragma once
#include <vector>

using namespace std;

class Observer {

public:
    Observer();
    virtual void update() = 0;
    virtual ~Observer();

};

class Subject
{
private:
    vector<Observer*> observers;

public:
    Subject();
    void addObserver(Observer *o);
    void notifyAllObservables();
    ~Subject();
};

