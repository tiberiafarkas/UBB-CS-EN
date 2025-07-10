//
// Created by Dragos on 6/30/2022.
//

#include "Observer.h"

Observer::~Observer() {

}

void Subject::addObserver(Observer *o) {
    arr.push_back(o);
}

void Subject::notify() {
    for(auto o:arr){
        o->update();
    }
}
