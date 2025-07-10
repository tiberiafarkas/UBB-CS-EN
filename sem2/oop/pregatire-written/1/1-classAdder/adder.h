#pragma once
#include <vector>

using std::vector;

template<typename T>
class Adder {
private:
	vector<T> v;

public:
	Adder() {

	};

	Adder(T initial) {
		v.push_back(initial);
	}

	~Adder() {
		v.clear();
	}

	Adder& operator+(T value) {
		v.push_back(value); // add value to the vector
		return *this; // return the current object
	}

	Adder& operator++() {
		if (v.empty()) {
			throw std::runtime_error("No more values!");
		}
		v.push_back(v.back()); // add the last value again
		return *this; // return the current object
	}

	Adder& operator--() {
		if (v.empty()) {
			throw std::runtime_error("No more values!");
		}
		v.pop_back(); // remove the last value
		return *this; // return the current object
	}

	T sum() const {
		T s{}; //we use {} to initialize s to the default value of type T
		for ( auto i: v ) {
			s += i; // accumulate the sum of all values in the vector
		}
		return s; // return the total sum
	}
};