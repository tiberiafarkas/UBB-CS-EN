//
// Created by Dragos on 6/30/2022.
//

#ifndef CODE_REVISION_PREPO_H
#define CODE_REVISION_PREPO_H
#include "Programmer.h"

class PRepo {
private:
    vector<Programmer> programmers;
    string file_name = "Programmers.txt";
public:
    PRepo();

    virtual ~PRepo();

    void read_from_file();
    void save_to_file();
    vector<Programmer>& getAll();
};


#endif //CODE_REVISION_PREPO_H
