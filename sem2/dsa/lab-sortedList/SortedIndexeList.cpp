#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>


SortedIndexedList::SortedIndexedList(Relation r) {
	//TODO - Implementation
	this->root = nullptr; // Initialize the root of the tree
	this->r = r; // Set the relation for sorting
	this->size_bst = 0; // Initialize the size of the binary search tree
}

int SortedIndexedList::size() const {
	//TODO - Implementation
	return size_bst; // Return the size of the binary search tree
}

bool SortedIndexedList::isEmpty() const {
	//TODO - Implementation
	return size_bst == 0; // Check if the size of the binary search tree is zero
}

//BC: Theta(n) no element must be removed
//WC: Theta(n*h) because it calls remove and search 
//TC: Theta(n*h)
void SortedIndexedList::filter(Condition cond) {
	ListIterator it = this->iterator(); // Create an iterator for the list
	while (it.valid()) {
		TComp current = it.getCurrent(); // Get the current element
		if (!cond(current)) { // If the condition is not met
			int pos = this->search(current); // Find the position of the current element
			this->remove(pos); // Remove the element from the list
		}
		else {
			it.next(); // Move to the next element if the condition is met
		}
	}
}

//BC: Theta(1) the element is the root
//WC: Theta(h) h - the height of the tree
//TC: O(h) 
TComp SortedIndexedList::getElement(int i) const{
	//TODO - Implementation
	if (i < 0 || i >= size_bst) {
		throw std::exception();
	}

	Node* current = this->root;
	int pos = 0;
	while (current != nullptr) {
		if (i == pos + current->elements_to_the_left)
			return current->info;
		else if (i < pos + current->elements_to_the_left) {
			current = current->left; // Move to the left subtree
		}
		else {
			pos += current->elements_to_the_left + 1; // Update position and move to the right subtree
			current = current->right;
		}
	}
	return NULL_TCOMP; // If the element is not found, return NULL_TCOMP
}

//BC: Theta(1) the element is the root
//WC: Theta(h) h - the height of the tree
//TC: O(h)
TComp SortedIndexedList::remove(int i) {
	//TODO - Implementation
	if (i < 0 || i >= size_bst) {
		throw std::exception();
	}

	Node* current = this->root;
	Node* parent = nullptr;
	int pos = 0;

	while (current != nullptr) { 
		if (i == pos + current->elements_to_the_left)
			break;
		else if (i < pos + current->elements_to_the_left) {
			parent = current; // Update parent to current before moving left
			current = current->left; // Move to the left subtree
		}
		else {
			pos += current->elements_to_the_left + 1; // Update position and move to the right subtree
			parent = current; // Update parent to current before moving right
			current = current->right;
		}
	}

	if (current == nullptr) {
		throw std::exception(); // If the current node is null, throw an exception
	}

	TComp deletedCurrent = current->info; // Store the value to be deleted

	//has no children
	if (current->left == nullptr && current->right == nullptr) {
		decreaseLeftPositions(i); // Decrease the left positions of nodes after removal

		if (parent == nullptr) {
			root = nullptr; // If the current node is the root, set root to nullptr
		}
		else  {
			if (this->r(current->info, parent->info)) {
				parent->left = nullptr; // Remove current from its parent's left child
			}
			else {
				parent->right = nullptr; // Remove current from its parent's right child
			}
			delete current; // Free the memory of the deleted node
		}
		size_bst--; // Decrease the size of the binary search tree
	}

	//has one child
	else if (current->left == nullptr || current->right == nullptr) {
		decreaseLeftPositions(i); // Decrease the left positions of nodes after removal
		
		if (parent == nullptr) {
			root = (current->left != nullptr) ? current->left : current->right; // If the current node is the root, set root to its child
		}
		else {
			if (this->r(current->info, parent->info)) {
				parent->left = (current->left != nullptr) ? current->left : current->right; // Set parent's left child to current's child
			}
			else {
				parent->right = (current->left != nullptr) ? current->left : current->right; // Set parent's right child to current's child
			}
			delete current; // Free the memory of the deleted node
		}
		size_bst--; // Decrease the size of the binary search tree
	}

	//has 2 children
	else {
		TComp nextValue = successor(current->info); // Find the successor of the current node
		remove(search(nextValue)); // Remove the successor node
		current->info = nextValue; // Replace current's info with the successor's info
	}

	// Update the size of the binary search tree
	return deletedCurrent; // Return the value that was deleted
}

//BC: Theta(1) the element is the root
//WC: Theta(h) h - the height of the tree
//TC: O(h)
void SortedIndexedList::decreaseLeftPositions(int pos) {
	//TODO - Implementation
	Node* current = this->root;
	int currentPos = 0;
	while (current != nullptr) {
		if (pos == currentPos + current->elements_to_the_left) {
			return;
		}
		else if (pos < currentPos + current->elements_to_the_left) {
			current->elements_to_the_left--; // Decrease the count of elements to the left
			current = current->left; // Move to the left subtree
		}
		else {
			currentPos += current->elements_to_the_left + 1; // Update position and move to the right subtree
			current = current->right;
		}
	}
}

//BC: Theta(1) the element is the root
//WC: Theta(h) h - the height of the tree
//TC: O(h)
TComp SortedIndexedList::successor(TComp e) {
	//TODO - Implementation
	Node* current = this->root;

	while (current->info != e) {
		if (current == nullptr) {
			throw std::exception(); // If the element is not found, throw an exception
		}
		else if (this->r(e, current->info)) {
			current = current->left; // Move to the left subtree
		}
		else {
			current = current->right; // Move to the right subtree
		}
	}

	if (current->right != nullptr) {
		current = current->right; // Move to the right subtree
		while (current->left != nullptr) {
			current = current->left; // Find the leftmost node in the right subtree
		}
		return current->info; // Return the successor value
	}
	else {
		int p = parent(current->info); // Find the parent of the element
		Node* parent = this->root;

		while (parent != nullptr && parent->info != p) {
			if (this->r(e, parent->info)) {
				parent = parent->left; // Move to the left subtree
			}
			else {
				parent = parent->right; // Move to the right subtree
			}
		}

		while (parent != nullptr && parent->left != current) {
			current = parent; // Move up the tree until we find the parent of the current node
			int newp = this->parent(current->info); // Get the parent of the current node
			Node* newParent = this->root;

			while (newParent != nullptr && newParent->info != newp) {
				if (this->r(e, newParent->info)) {
					newParent = newParent->left; // Move to the left subtree
				}
				else {
					newParent = newParent->right; // Move to the right subtree
				}
			}

			parent = newParent; // Update parent to the new parent found
		}
		if (parent == nullptr) {
			throw std::exception(); // If the parent is null, throw an exception
		}
		else {
			return parent->info; // Return the parent's info as the successor
		}
	}
}

//BC: Theta(1) the element is the root
//WC: Theta(h) h - the height of the tree
//TC: O(h)
TComp SortedIndexedList::parent(TComp e) {
	//TODO - Implementation
	Node* current = this->root;

	if (current->info == e)
		return -1; // If the element is the root, it has no parent
	else {
		while (current != nullptr && 
			(current->left == nullptr || current->left->info != e) &&
			(current->right == nullptr || current->right->info != e)) {
			if (this->r(e, current->info)) {
				current = current->left; // Move to the left subtree
			}
			else {
				current = current->right; // Move to the right subtree
			}
		}
		if (current != nullptr) {
			return current->info; // Return the parent node if found
		}
		else {
			throw std::exception(); // If the element is not found, throw an exception
		}
	}
}

//BC: Theta(1) the element is the root
//WC: Theta(h) h - the height of the tree
//TC: O(h)
int SortedIndexedList::search(TComp e) const {
	//TODO - Implementation
	Node* current = this->root;
	int pos = 0;
	while (current != nullptr) {
		if (current->info == e) {
			return pos + current->elements_to_the_left; // Return the position of the found element
		}
		else if (this->r(e, current->info)) {
			current = current->left; // Move to the left subtree
		}
		else {
			pos += current->elements_to_the_left + 1; // Update position and move to the right subtree
			current = current->right; // Move to the right subtree
		}
	}
	// If the element is not found, return -1
	return -1;
}


////BC: Theta(1) the element is the root
//WC: Theta(h)
//TC: O(h)
void SortedIndexedList::add(TComp e) {
	//TODO - Implementation
	Node* newNode = new Node{ e, nullptr, nullptr, 0 }; // Create a new node with the element
	if (root == nullptr) {
		root = newNode; // If the tree is empty, set the new node as the root
		size_bst++;
		return;
	}

	Node* current = root;
	Node* parent = nullptr;
	while (current != nullptr) {
		parent = current; // Keep track of the parent node
		if (this->r(e, current->info)) {
			current->elements_to_the_left++; // Increment the count of elements to the left
			current = current->left; // Move to the left subtree
		}
		else {
			current = current->right; // Move to the right subtree
		}
	}

	if (this->r(e, parent->info)) {
		parent->left = newNode; // Add the new node as the left child of the parent
	}
	else {
		parent->right = newNode; // Add the new node as the right child of the parent
	}

	size_bst++; // Increment the size of the binary search tree
}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	//TODO - Implementation
	while (!this->isEmpty()) {
		try {
			this->remove(0); // Remove the first element until the list is empty
		}
		catch (exception&) {
			break; // If an exception occurs, break the loop
		}
	}
}
