#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	//TODO - Implementation
	currentIndex = 0; // Initialize the current index to 0
}


//TC: Theta(1)
void ListIterator::first(){
	//TODO - Implementation
	currentIndex = 0; // Reset the current index to the first element
}

////TC: Theta(1)
void ListIterator::next(){
	//TODO - Implementation
	if (!valid()) {
		throw std::exception(); // Throw an exception if the iterator is not valid
	}
	currentIndex++; // Move to the next index
}

//TC: Theta(1)
bool ListIterator::valid() const{
	//TODO - Implementation
	return currentIndex < list.size(); // Check if the current index is within the bounds of the list size
}

//TC: Theta(1)
TComp ListIterator::getCurrent() const{
	//TODO - Implementation
	if (!valid()) {
		throw std::exception(); // Throw an exception if the iterator is not valid
	}
	return list.getElement(currentIndex); // Return the current element at the current index
}


