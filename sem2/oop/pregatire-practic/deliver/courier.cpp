#include "courier.h"
#include <sstream>

using std::stringstream;

//the format of the file is
// name|street1,street2,street3,...|x,y,r

istream& operator>>(istream& is, Courier& courier) {
    string line;
    if (getline(is, line)) {
        stringstream ss(line);
        string name, streetsField, zoneField;

        // Read the three fields separated by '|'
        getline(ss, name, '|');
        getline(ss, streetsField, '|');
        getline(ss, zoneField);

        courier.name = name;
        courier.streets.clear();

        // Split streetsField by ','
        stringstream streetStream(streetsField);
        string street;
        while (getline(streetStream, street, ',')) {
            courier.streets.push_back(street);
        }

        // Parse zoneField: x,y,r
        stringstream zoneStream(zoneField);
        string x, y, r;
        getline(zoneStream, x, ',');
        getline(zoneStream, y, ',');
        getline(zoneStream, r);
        courier.zone.x = std::stoi(x);
        courier.zone.y = std::stoi(y);
        courier.zone.radius = std::stoi(r);
    }
    return is;
}


ostream& operator<<(ostream& os, Courier& courier) {
	os << courier.getName() << '|';
	for (auto street: courier.getStreets()) {
		os << street;
		if (&street != &courier.getStreets().back()) {
			os << ',';
		}
	}
	Circle zone = courier.getZone();
	os << '|' << zone.x << ',' << zone.y << ',' << zone.radius;
	return os;
}