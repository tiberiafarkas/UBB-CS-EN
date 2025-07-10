//
// Created by Dragos on 6/30/2022.
//

#ifndef CODE_REVISION_SREPO_H
#define CODE_REVISION_SREPO_H
#include "Source_File.h"

class SRepo {
private:
    vector<Source_File> source_files;
    string file_name = "Source_files.txt";
public:
    SRepo();

    virtual ~SRepo();

    void read_from_file();
    void save_to_file();
    vector<Source_File>& getAll();
    void add_sf(Source_File& sf);
};


#endif //CODE_REVISION_SREPO_H
