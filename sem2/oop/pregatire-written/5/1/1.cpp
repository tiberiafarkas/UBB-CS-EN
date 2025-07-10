#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Define the classes SmartPointer and Vector such that the following C++ code is correct. 
Enumerate the data members (including types) and the prototypes of all methods and 
implement the method allowing the operation emphasized in the code below.
*/

template<typename T>
class SmartPointer {
private:
	T* ptr;
	int* refCount;
public:
	SmartPointer(T* p = nullptr) : ptr(p), refCount(new int(1)) {}
	SmartPointer(const SmartPointer<T>& other) {
		ptr = other.ptr;
		refCount = other.refCount;
		(*refCount)++;
	}
	~SmartPointer() {
		if (--(*refCount) == 0) {
			delete ptr;
			delete refCount;
		}
	}
	SmartPointer& operator=(const SmartPointer<T>& other) {
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
	bool operator==(const SmartPointer<T>& other) const {
		return *ptr == *other.ptr;
	}
	T* operator->() const {
		return ptr;
	}
	T& operator*() const {
		return *ptr;
	}
};

template<typename T>
class Vector {
private:
	vector<T> elements;
public:
	Vector() = default;
	Vector<T>& add(const T& el) {
		elements.push_back(el);
		return *this;
	}

	Vector& operator-(const T& elem) {
		auto it = find(elements.begin(), elements.end(), elem);
		if (it != elements.end()) {
			elements.erase(it);
		}
		else {
			throw runtime_error("Element does not exist!");
		}
		return *this;
	}

	auto begin() { return elements.begin(); }
	auto end() { return elements.end(); }
};

void function() {
	SmartPointer<int> i1{ new int{ 1 } }; 
	SmartPointer<int> i2{ new int{ 2 } }; 
	SmartPointer<int> i3{ new int{ 3 } }; 
	Vector<SmartPointer<int>> v1{}; 
	v1.add(i1).add(i2).add(i3);
	for (auto e : v1)
		cout << *e << ", "; // prints 1, 2, 3

	SmartPointer<string> s1{ new string{ "A" } }; 
	SmartPointer<string> s2 = s1;
	SmartPointer<string> s3{ new string{ "C" } }; 
	Vector<SmartPointer<string>> v2{};
	v2.add(s2).add(s1);
	
	try {
		v2 = v2 - s2; // IMPLEMENT THIS OPERATION
		v2 = v2 - s3; // IMPLEMENT THIS OPERATION
	}
	catch (std::runtime_error& ex) {
		cout << ex.what(); // prints: "Element does not exist!"
	}
} // memory is correctly deallocated

int main()
{
	function();
	return 0;
}
