//
// Created by Dragos on 6/30/2022.
//

#ifndef CODE_REVISION_SERVICE_H
#define CODE_REVISION_SERVICE_H
#include "SRepo.h"
#include <algorithm>
#include "Observer.h"

class Service: public Subject {
private:
    SRepo& srepo;
public:
    Service(SRepo &srepo);

    virtual ~Service();

    vector<Source_File> sorted_by_name();
    bool search_sf(string name);
    void add_sf(string name, string creator);
    void revise(string name, string reviewer);
};


#endif //CODE_REVISION_SERVICE_H
