//
// Created by Dragos on 6/30/2022.
//

#ifndef CODE_REVISION_PROGRAMMER_H
#define CODE_REVISION_PROGRAMMER_H
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Programmer {
private:
    string name;
    int revised, must_revise;
public:
    Programmer(const string &name, int revised, int mustRevise);

    Programmer();

    virtual ~Programmer();

    const string &getName() const;

    void setName(const string &name);

    int getRevised() const;

    void setRevised(int revised);

    int getMustRevise() const;

    void setMustRevise(int mustRevise);

    friend ostream &operator<<(ostream &os, const Programmer &programmer);
    friend istream &operator>>(istream &is, Programmer &programmer);
};


#endif //CODE_REVISION_PROGRAMMER_H
