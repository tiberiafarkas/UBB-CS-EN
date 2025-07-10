#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

//BC: Theta(n)
//WC: Theta(n)
//TC: Theta(n)
MultiMap::MultiMap() {
	//TODO - Implementation
	capacity = 10;
	numberOfElements = 0;
	table = new Node * [capacity]();
	for (int i = 0; i < capacity; ++i) {
		table[i] = nullptr;
	}
}

//BC: Theta(1) 
//WC: Theta(n) 
//TC: O(n)
void MultiMap::add(TKey c, TValue v) {
	//TODO - Implementation
	if ( numberOfElements / capacity >= 0.75 ) { // rehash if load factor is 0.75 or more
		rehash();
	}
	int index = hashFunction(c);
	Node* current = table[index];
	while (current) {
		if (current->key == c) {
			current->addValue(v);
			numberOfElements++;
			return;
		}
		current = current->next;
	}
	if (current == nullptr) {
		Node* newNode = new Node(c, v);
		newNode->next = table[index];
		table[index] = newNode;
		numberOfElements++;
	}
}

//BC: Theta(1)
//WC: Theta(n)
//TC: O(n)
bool MultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
	int index = hashFunction(c);
	Node* current = table[index];
	Node* prev = nullptr;

	while (current) {
		if (current->key == c) {
			for (int i = 0; i < current->valueCount; ++i) {
				if (current->values[i] == v) {
					// Remove the value
					for (int j = i; j < current->valueCount - 1; ++j) {
						current->values[j] = current->values[j + 1];
					}
					current->valueCount--;
					numberOfElements--;
					if (current->valueCount == 0) {
						// Remove the node if no values left
						if (prev) {
							prev->next = current->next;
						}
						else {
							table[index] = current->next;
						}
						delete current;
					}
					return true;
				}
			}
		}
		prev = current;
		current = current->next;
	}

	return  false;
}


//BC: Theta(1)
//WC: Theta(n)
//TC: O(n)
vector<TValue> MultiMap::search(TKey c) const {
	//TODO - Implementation

	int index = hashFunction(c);
	Node* current = table[index];
	while (current) {
		if (current->key == c) {
			vector<TValue> values;
			for (int i = 0; i < current->valueCount; ++i) {
				values.push_back(current->values[i]);
			}
			return values;
		}
		current = current->next;
	}

	return vector<TValue>();
}


//BC: Theta(1)
//WC: Theta(1)
//TC: Theta(1)
int MultiMap::size() const {
	//TODO - Implementation
	return numberOfElements;
}


//BC: Theta(1)
//WC: Theta(1)
//TC: Theta(1)
bool MultiMap::isEmpty() const {
	//TODO - Implementation
	return numberOfElements == 0;
}

//BC: Theta(n+m)
//WC: Theta(n^2)
//TC: O(n^2)
int MultiMap::addIfNotPresent(MultiMap& m) {
	int count = 0;
	for (int i = 0; i < m.capacity; ++i) {
		Node* current = m.table[i];
		while (current) {
			if (search(current->key).empty()) {
				add(current->key, current->values[0]);
				count++;
			}
			current = current->next;
		}
	}
	return count;
}

//BC: Theta(1)
//WC: Theta(1)
//TC: Theta(1)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

//BC: Theta(n)
//WC: Theta(n)
//TC: Theta(n)
MultiMap::~MultiMap() {
	//TODO - Implementation
	for (int i = 0; i < capacity; ++i) {
		Node* current = table[i];
		while (current) {
			Node* toDelete = current;
			current = current->next;
			delete toDelete;
		}
	}
	delete[] table;
}

