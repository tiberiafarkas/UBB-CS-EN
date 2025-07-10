//
// Created by Dragos on 6/30/2022.
//

#include "Service.h"

Service::Service(SRepo &srepo) : srepo(srepo) {}

Service::~Service() {

}

vector<Source_File> Service::sorted_by_name() {
    vector<Source_File> sf = srepo.getAll();
    sort(sf.begin(), sf.end(), [](Source_File s1, Source_File s2){return s1.getName()<s2.getName();});
    return sf;
}

void Service::add_sf(string name, string creator) {
    Source_File sf(name, "not revised", creator, "no one");
    srepo.add_sf(sf);
    notify();
}

bool Service::search_sf(string name) {
    for(auto sf:srepo.getAll()){
        if(sf.getName() == name)
            return false;
    }
    return true;
}

void Service::revise(string name, string reviewer) {
    for(auto& sf:srepo.getAll()){
        if(sf.getName() == name){
            sf.setReviewer(reviewer);
            sf.setStatus("revised");
        }
    }
    notify();
}
