#pragma once
//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TCOMP -11111

typedef struct Node {
	TComp info;
	Node* left;
	Node* right;
	int elements_to_the_left; // number of elements in the left subtree
};

typedef bool (*Condition)(TComp);

class SortedIndexedList {
private:
	friend class ListIterator;
private:
	//TODO - Representation

	Node* root;
	Relation r;
	int size_bst; // size of the binary search tree

public:
	// constructor
	SortedIndexedList(Relation r);

	// returns the size of the list
	int size() const;

	//checks if the list is empty
	bool isEmpty() const;

	// returns an element from a position
	//throws exception if the position is not valid
	TComp getElement(int pos) const;

	// adds an element in the sortedList (to the corresponding position)
	void add(TComp e);

	// removes an element from a given position
	//returns the removed element
	//throws an exception if the position is not valid
	TComp remove(int pos);

	// decreases all the left positions of the nodes when a node is removed
	void decreaseLeftPositions(int pos);

	// returns the successor of an element in the list
	// returns NULL_TCOMP if the element is the last in the list or throws an exception if the element is not in the list
	TComp successor(TComp e);

	// returns the parent of an element in the list
	// returns nullptr if the element is the root or trows an exception if the element is not in the list
	TComp parent(TComp e);

	// searches for an element and returns the first position where the element appears or -1 if the element is not in the list
	int search(TComp e) const;

	//keeps in the sortedlist only the elements that respect the given condition
	void filter(Condition cond);

	// returns an iterator set to the first element of the list or invalid if the list is empty
	ListIterator iterator();

	//destructor
	~SortedIndexedList();

};
