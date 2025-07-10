#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;


FixedCapBiMapIterator::FixedCapBiMapIterator(FixedCapBiMap& d) : map(d)
{
	//TODO - Implementation
	this->currentPos = 0;
}


void FixedCapBiMapIterator::first() {
	//TODO - Implementation
	this->currentPos = 0;
}


void FixedCapBiMapIterator::next() {
	//TODO - Implementation
	if (this->currentPos == this->map.mapSize)
		throw exception("Invalid position");
	this->currentPos++;
}


TElem FixedCapBiMapIterator::getCurrent(){
	//TODO - Implementation
	if (this->currentPos == this->map.mapSize)
		throw exception("Invalid position");
	return this->map.elements[this->currentPos];
}

TElem FixedCapBiMapIterator::removeCurrent() {
	//TODO - Implementation
	if (this->currentPos >= this->map.mapSize) //throw exception if the iterator is not valid
		throw exception("Invalid position");

	TElem removed = this->map.elements[this->currentPos];
	for (int i = this->currentPos; i < this->map.mapSize - 1; i++) {
		this->map.elements[i] = this->map.elements[i + 1];
	}
	this->map.mapSize--;

	return removed;
}

bool FixedCapBiMapIterator::valid() const {
	//TODO - Implementation
	if (this->currentPos < this->map.mapSize)
		return true;
	return false;
}



