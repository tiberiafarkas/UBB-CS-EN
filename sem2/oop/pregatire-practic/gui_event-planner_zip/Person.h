#pragma once

#include <string>

using namespace std;

class Person {

private:
    string name;
    float latitude, longitude;
    bool status;

public:
    Person(string name, float latitude, float longitude, bool status);
    Person();

    string getName();
    float getLatitude();
    float getLongitude();
    bool getStatus();
};

