#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111
typedef int TElem;
class SetIterator;

struct node {
	TElem info;
	int next;
	int prev;
};

class Set {
	//DO NOT CHANGE THIS PART
	friend class SetIterator;

    //set implemented as a doubly linked list on an array

    private:
		//TODO - Representation
		int capacity;
		int sizeSet;
		int firstEmpty;
        int head;
        node* nodes;
        void resizeArray();

    public:
        //implicit constructor
        Set();

        //adds an element to the set
		//returns true if the element was added, false otherwise (if the element was already in the set and it was not added)
        bool add(TElem e);

        //removes an element from the set
		//returns true if e was removed, false otherwise
        bool remove(TElem e);

        //checks whether an element belongs to the set or not
        bool search(TElem elem) const;

        //returns the number of elements;
        int size() const;

        //check whether the set is empty or not;
        bool isEmpty() const;

        //return an iterator for the set
        SetIterator iterator() const;

        //adds all elements of s into this set
		void _union(const Set& s);

        // destructor
        ~Set();

};





