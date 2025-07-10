//
// Created by Dragos on 6/30/2022.
//

#ifndef CODE_REVISION_SOURCE_FILE_H
#define CODE_REVISION_SOURCE_FILE_H
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Source_File {
private:
    string name, status, creator, reviewer;
public:
    Source_File(const string &name, const string &status, const string &creator, const string &reviewer);

    Source_File();

    virtual ~Source_File();

    const string &getName() const;

    void setName(const string &name);

    const string &getStatus() const;

    void setStatus(const string &status);

    const string &getCreator() const;

    void setCreator(const string &creator);

    const string &getReviewer() const;

    void setReviewer(const string &reviewer);

    friend ostream &operator<<(ostream &os, const Source_File &file);
    friend istream &operator>>(istream &is, Source_File &file);

    bool is_revised();
};


#endif //CODE_REVISION_SOURCE_FILE_H
