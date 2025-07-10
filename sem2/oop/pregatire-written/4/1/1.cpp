#include <iostream>
#include <cassert>
#include <vector>
#include <memory>
using namespace std;

/*
Define the classes Object, Character, Double and MyObjects such that the following C++ 
code is correct and memory is correctly managed. Enumerate the data members 
(including types) and the prototypes of all methods and implement the method allowing 
the operation emphasized in the code below.
*/

class Object {
public: 
	virtual ~Object() = default;
	virtual void print() = 0; // Pure virtual function for printing
};

class Character : public Object {
private:
    char c;
public:
    Character(char c) : c(c) {}
	void print() override { 
        std::cout << c << " "; 
    }
	bool operator==(char other) const {
		return c == other;
	}
};

class Double : public Object {
private:
	double d;
public:
	Double(double d) : d(d) {}
	void print() override {
		std::cout << d << " ";
	}
	bool operator==(double other) const {
		return d == other;
	}
};

class MyObjects {
private:
	vector<Object*> objects;
public:
	MyObjects(Object *obj) {
		objects.push_back(obj);
	}
	MyObjects& addBeginning(Object *obj) {
		objects.insert(objects.begin(), obj);
		return *this;
	}
	int size() {
		return objects.size();
	}
	auto begin() { return objects.begin(); }
	auto end() { return objects.end(); }

	~MyObjects() {
		for (Object* obj : objects) {
			delete obj; // Free memory for each object
		}
	}
};

void function() {
    Character* c = new Character{ 'c' }; 
    assert(*c == 'c');
    MyObjects objects{ c };
    objects.addBeginning(new Double{ 2.5 }).addBeginning(new Double{ 1.2 }).addBeginning(new Character{ 'o' }); // IMPLEMENT THIS OPERATION
    assert(objects.size() == 4);
    // prints o 1.2 2.5 c for (Object o: objects) ->print();
	for (Object* o : objects) {
		o->print();
	}
}

int main()
{
	function();
	return 0;
}
