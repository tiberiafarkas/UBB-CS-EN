#include "Set.h"
#include "SetITerator.h"
#include <exception>

//BC: Theta(n)
//WC: Theta(n)
//TC: Theta(n)
Set::Set() {
	//TODO - Implementation
	this->capacity = 10;
	this->sizeSet = 0;
	this->nodes = new node[this->capacity];
	this->head = -1; 

	for (int i = 0; i < this->capacity; i++) {
		this->nodes[i].next = i + 1;
		this->nodes[i].prev = -1;
	}
	this->nodes[this->capacity - 1].next = -1;
	this->firstEmpty = 0;
}

//function to resize the array
//BC: Theta(n)
//WC: Theta(n)
//TC: Theta(n)
void Set::resizeArray() {
	int oldCapacity = this->capacity;
	this->capacity *= 2;
	node* newNodes = new node[this->capacity];

	for (int i = 0; i < oldCapacity; i++) {
		newNodes[i] = this->nodes[i];
	}
	for (int i = oldCapacity; i < this->capacity; i++) {
		newNodes[i].next = i + 1;
		newNodes[i].prev = -1;
	}
	newNodes[this->capacity - 1].next = -1;
	newNodes[this->capacity - 1].prev = -1;

	delete[] this->nodes;
	this->nodes = newNodes;
	this->firstEmpty = oldCapacity;
}

//BC: Theta(1) - if the element is at the head
//WC: Theta(n) - if the element is not found
//TC: O(n) 
bool Set::add(TElem elem) {
	//TODO - Implementation
	if (search(elem)) {
		return false; // Element already exists
	}
	if (this->firstEmpty == -1) {
		resizeArray();
	}
	int newNodeIndex = this->firstEmpty;
	this->firstEmpty = this->nodes[this->firstEmpty].next;
	this->nodes[newNodeIndex].info = elem;
	this->nodes[newNodeIndex].next = this->head;
	this->nodes[newNodeIndex].prev = -1;

	if (this->head != -1) {
		this->nodes[this->head].prev = newNodeIndex;
	}

	this->head = newNodeIndex;
	this->sizeSet++;
	return true;
}


//BC: Theta(1) - if the element is at the head
//WC: Theta(n) - if the element is not found
//TC: O(n) 
bool Set::remove(TElem elem) {
	//TODO - Implementation
	int current = this->head;
	while (current != -1 && this->nodes[current].info != elem) {
		current = this->nodes[current].next;
	}
	if (current == -1) {
		return false; // Element not found
	}
	if (this->nodes[current].prev != -1) {
		this->nodes[this->nodes[current].prev].next = this->nodes[current].next;
	}
	else {
		this->head = this->nodes[current].next; // Update head if necessary
	}
	if (this->nodes[current].next != -1) {
		this->nodes[this->nodes[current].next].prev = this->nodes[current].prev;
	}

	this->nodes[current].next = this->firstEmpty;
	this->nodes[current].prev = -1;
	this->firstEmpty = current; // Add to the list of free nodes
	this->sizeSet--;
	return true; // Element removed
}

//BC: Theta(1) - if the element is at the head
//WC: Theta(n) - if the element is not found
//TC: O(n)
bool Set::search(TElem elem) const {
	//TODO - Implementation
	int current = this->head;
	while (current != -1) {
		if (this->nodes[current].info == elem) {
			return true; // Element found
		}
		current = this->nodes[current].next;
	}
	return false; // Element not found
}

//TC: Theta(1)
int Set::size() const {
	//TODO - Implementation
	return this->sizeSet;
}

//TC: Theta(1)
bool Set::isEmpty() const {
	//TODO - Implementation
	return this->sizeSet == 0;
}

//TC: Theta(n) - we have to traverse all elements
void Set::_union(const Set& s) {
	//TODO - Implementation
	SetIterator it = s.iterator();
	it.first();
	while (it.valid()) {
		this->add(it.getCurrent());
		it.next();
	}
}

Set::~Set() {
	//TODO - Implementation
	delete[] this->nodes;
}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}


