#include "SetIterator.h"
#include "Set.h"
#include <exception>


//TC: Theta(1)
SetIterator::SetIterator(const Set& m) : set(m)
{
	//TODO - Implementation
	this->current = m.head; // Initialize current to the head of the set
}


//TC: Theta(1)
void SetIterator::first() {
	//TODO - Implementation
	this->current = this->set.head; // Set current to the head of the set
}

//TC: Theta(1)
void SetIterator::next() {
	//TODO - Implementation
	if (!valid()) {
		throw std::exception();
	}
	this->current = this->set.nodes[this->current].next; // Move to the next element
}

//TC: Theta(1)
TElem SetIterator::getCurrent()
{
	//TODO - Implementation
	if (!valid()) {
		throw std::exception();
	}
	return this->set.nodes[this->current].info; // Return the current element
}

//TC: Theta(1)
bool SetIterator::valid() const {
	//TODO - Implementation
	return this->current != -1; // Check if the current position is valid

}



