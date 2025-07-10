#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Define the classes SmartPointer and Set such that the following C++ code is correct.\
// Enumerate the data members(including types) and the prototypes of all methods and \
// implement the method allowing the operation shown emphasized in the code below.

template<typename T>
class SmartPointer {
private:
    T* ptr;
    int* refCount;
public:
    SmartPointer(T* p = nullptr) : ptr(p), refCount(new int(1)) {}
    ~SmartPointer() { 
		if (--(*refCount) == 0) {
			delete ptr;
			delete refCount;
		}
	}
    // Copy constructor
    SmartPointer(const SmartPointer& other) : ptr(other.ptr), refCount(other.refCount) {
		++(*refCount);
    }

    // Assignment operator
    SmartPointer& operator=(const SmartPointer& other) {
        if (this != &other) {
			if (--(*refCount) == 0) {
				delete ptr;
				delete refCount;
			}
			ptr = other.ptr;
			refCount = other.refCount;
			++(*refCount);
        }
        return *this;
    }
    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }

	bool operator==(SmartPointer& other) {
		return *ptr == *other.ptr;
	}
};

template<typename T>
class Set {
private:
    vector<T> array;
public:
    Set() {};

    Set<T>& operator+(T& elem) {
        for (auto& e: array) {
            if (e == elem)
				throw runtime_error("Element already exists!");
        }

		array.push_back(elem);
		return *this;
	}

    Set<T>& remove(T& elem) {
		for (auto it = array.begin(); it != array.end(); ++it) {
			if (*it == elem) {
				array.erase(it);
				return *this;
			}
		}
    }

    auto begin() { return array.begin(); }
    auto end() { return array.end(); }
};

void function2() {
    SmartPointer<string> s1{ new string{ "A" } };
    SmartPointer<string> s2 = s1;
    SmartPointer<string> s3{ new string{ "C" } }; 
    Set<SmartPointer<string>> set1{};
    
    try {
        set1 = set1 + s1; // IMPLEMENT THIS OPERATION 
        set1 = set1 + s2; // IMPLEMENT THIS OPERATION 
    }
    catch (std::runtime_error& ex) {
        cout << ex.what(); // prints: "Element already exists!"
    }
    
    SmartPointer<int> i1{ new int{ 1 } };
    SmartPointer<int> i2{ new int{ 2 } };
    SmartPointer<int> i3{ new int{ 3 } }; 
    Set<SmartPointer<int>> set2{};

    set2 = set2 + i1; // IMPLEMENT THIS OPERATION
    set2 = set2 + i2; // IMPLEMENT THIS OPERATION 
    set2 = set2 + i3; // IMPLEMENT THIS OPERATION 
    set2.remove(i1).remove(i3);
    for (auto e : set2)
        cout << *e << ", "; // prints 2,
} // memory is correctly deallocated

int main()
{
	function2();
	return 0;
}

