

#include "Observer.h"

void Subject::addObserver(Observer *o) {
    this->observers.push_back(o);

}

void Subject::notifyAllObservables() {
    for(auto o:this->observers)
        o->update();

}

Subject::~Subject() = default;

Subject::Subject() = default;

Observer::Observer() = default;

Observer::~Observer() = default;
