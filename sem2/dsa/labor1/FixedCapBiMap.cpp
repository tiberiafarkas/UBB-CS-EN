#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"

FixedCapBiMap::FixedCapBiMap(int capacity) {
	//TODO - Implementation
	if (capacity <= 0)
		throw std::exception("Invalid capacity");

	this->capacity = capacity;
	this->mapSize = 0;
	this->elements = new TElem[this->capacity];

}

FixedCapBiMap::~FixedCapBiMap() {
	//TODO - Implementation
	delete[] this->elements;
}

bool FixedCapBiMap::add(TKey c, TValue v){
	//TODO - Implementation
	if (capacity == mapSize) 
		throw exception("Map is full");

	int count = 0;
	for (int i = 0; i < this->mapSize && count < 2; i++) {
		if (this->elements[i].first == c) {
			count++;
		}
	}

	if (count == 2) {
		return false;
	}

	this->elements[this->mapSize++] = { c, v };


	return true;
}

ValuePair FixedCapBiMap::search(TKey c) const{
	//TODO - Implementation
	ValuePair result;
	result.first = NULL_TVALUE;
	result.second = NULL_TVALUE;

	int count = 0;
	for (int i = 0; i < this->mapSize && count < 2; i++) {
		if (this->elements[i].first == c) {
			if (count == 0) {
				result.first = this->elements[i].second;
				count++;
			}
			else {
				result.second = this->elements[i].second;
				break;
			}
		}
	}

	return result;
}

bool FixedCapBiMap::remove(TKey c, TValue v){
	//TODO - Implementation
	//BC: Theta(1)
	//WC: Theta(n)
	//TC: O(n)
	for (int i = 0; i < this->mapSize; ++i) {
		if (this->elements[i].first == c && this->elements[i].second == v) {
			this->elements[i] = this->elements[this->mapSize - 1];
			this->mapSize--;
			return true;
		}
	}
	return false;
}


int FixedCapBiMap::size() const {
	//TODO - Implementation
	return mapSize;
}

bool FixedCapBiMap::isEmpty() const{
	//TODO - Implementation
	return this->mapSize == 0;
}

bool FixedCapBiMap::isFull() const {
	//TODO - Implementation
	return this->mapSize == this->capacity;
}

FixedCapBiMapIterator FixedCapBiMap::iterator() {
	return FixedCapBiMapIterator(*this);
}



