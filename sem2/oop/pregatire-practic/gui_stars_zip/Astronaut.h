
#include <iostream>

class Astronaut {
private:
    std::string name, constellation;
public:
    Astronaut(std::string name = "", std::string constellation = "") : name{ name }, constellation{ constellation } {};
    [[nodiscard]] std::string getName() const { return this->name; }
    [[nodiscard]] std::string getConstellation() const { return this->constellation; }
};

