#include "MultiMapIterator.h"
#include "MultiMap.h"


// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	//TODO - Implementation
	current = nullptr;
	currentIndex = 0;
	currentValueIndex = 0;
	first();
}

// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)
TElem MultiMapIterator::getCurrent() const{
	//TODO - Implementation
	if (!valid()) {
		throw std::exception();
	}
	return TElem(current->key, current->values[currentValueIndex]);
}

// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)
bool MultiMapIterator::valid() const {
	//TODO - Implementation
	if (current == nullptr) {
		return false;
	}
	return true;
}

// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)
void MultiMapIterator::next() {
	//TODO - Implementation
	if (!valid()) {
		throw std::exception();
	}
	if (currentValueIndex < current->valueCount - 1) {
		currentValueIndex++;
	}
	else {
		currentValueIndex = 0;
		current = current->next;
		if (current == nullptr) {
			currentIndex++;
			while (currentIndex < col.capacity && col.table[currentIndex] == nullptr) {
				currentIndex++;
			}
			if (currentIndex < col.capacity) {
				current = col.table[currentIndex];
			}
			else {
				current = nullptr;
			}
		}
	}
}

// BC: Theta(1)
// WC: Theta(1)	
// TC: Theta(1)
void MultiMapIterator::first() {
	//TODO - Implementation
	currentIndex = 0;
	while (currentIndex < col.capacity && col.table[currentIndex] == nullptr) {
		currentIndex++;
	}
	if (currentIndex < col.capacity) {
		current = col.table[currentIndex];
		currentValueIndex = 0;
	}
	else {
		current = nullptr;
	}
}

