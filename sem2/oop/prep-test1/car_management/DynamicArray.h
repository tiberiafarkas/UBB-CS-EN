#pragma once

template<typename TElem>

class DynamicArray {
private:
	TElem* elems;
	int size;
	int capacity;

	//resize the array, double the capacity
	void resize();

public:
	//default constructor
	DynamicArray(int capacity = 10);

	//copy constructor
	DynamicArray(const DynamicArray& v);

	//destructor
	~DynamicArray();

	//assignment operator
	DynamicArray& operator=(const DynamicArray& v);

	//overloading the subscript operator
	TElem& operator[](int pos);
	const TElem& operator[](int pos) const;

	//adds an element to the array
	void add(const TElem& e);

	//removes an element from a given position
	void remove(int pos);

	//updates an element from a given position
	void update(int pos, const TElem& e);

	//returns the size of the array
	int getSize() const;

	//find the position of an element
	int find(const TElem& e);

	//returns a copy
	DynamicArray copy();

};

template<typename TElem>
DynamicArray<TElem>::DynamicArray(int capacity) {
	this->size = 0;
	this->capacity = capacity;
	this->elems = new TElem[capacity];
}

template<typename TElem>
DynamicArray<TElem>::DynamicArray(const DynamicArray& v) {
	this->size = v.size;
	this->capacity = v.capacity;
	this->elems = new TElem[this->capacity];
	for (int i = 0; i < this->size; ++i) {
		this->elems[i] = v.elems[i];
	}
}

template<typename TElem>
DynamicArray<TElem>::~DynamicArray() {
	delete[] this->elems;
}

template<typename TElem>
DynamicArray<TElem>& DynamicArray<TElem>::operator=(const DynamicArray& v) {
	if (this == &v) {
		return *this;
	}
	this->size = v.size;
	this->capacity = v.capacity;

	TElem* aux = new TElem[this->capacity];
	delete[] this->elems;

	this->elems = aux;
	for (int i = 0; i < this->size; ++i) {
		this->elems[i] = v.elems[i];
	}
	return *this;
}

template<typename TElem>
TElem& DynamicArray<TElem>::operator[](int pos) {
	return this->elems[pos];
}

template<typename TElem>
const TElem& DynamicArray<TElem>::operator[](int pos) const {
	return this->elems[pos];
}

template<typename TElem>
void DynamicArray<TElem>::add(const TElem& e) {
	if (this->size == this->capacity) {
		this->resize();
	}
	this->elems[this->size++] = e;
}

template<typename TElem>
void DynamicArray<TElem>::remove(int pos) {
	for (int i = pos; i < this->size - 1; ++i) {
		this->elems[i] = this->elems[i + 1];
	}
	this->size--;
}

template<typename TElem>
int DynamicArray<TElem>::getSize() const {
	return this->size;
}

template<typename TElem>
void DynamicArray<TElem>::update(int pos, const TElem& e) {
	this->elems[pos] = e;
}

template<typename TElem>
int DynamicArray<TElem>::find(const TElem& e) {
	for (int i = 0; i < this->size; ++i) {
		if (this->elems[i] == e) {
			return i;
		}
	}
	return -1;
}

template<typename TElem>
void DynamicArray<TElem>::resize() {
	this->capacity *= 2;

	TElem* el = new TElem[this->capacity];
	for (int i = 0; i < this->size; ++i) {
		el[i] = this->elems[i];
	}

	delete[] this->elems;
	this->elems = el;
}

template<typename TElem>
DynamicArray<TElem> DynamicArray<TElem>::copy() {
	DynamicArray<TElem> copy;
	for (int i = 0; i < this->size; ++i) {
		copy.add(this->elems[i]);
	}
	return copy;
}