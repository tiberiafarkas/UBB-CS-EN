#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedIndexedList.h"
#include "ListIterator.h"
#include <assert.h>


//order relation - ascending
bool asc1(TComp c1, TComp c2) {
	if (c1 <= c2) {
		return true;
	}
	else {
		return false;
	}
}

bool Condition1(TComp e) {
	//keeps only the elements smaller than 10
	return e <= 10; // Example condition: keep elements smaller than 10
}

bool Condition2(TComp e) {
	//keeps only the elements greater than 10
	return e % 2 == 0; // Example condition: keep elements greater than 10
}

void test_filter() {
	SortedIndexedList list = SortedIndexedList(asc1);
	list.add(10);
	list.add(2);
	list.add(13);
	list.add(5);
	list.add(56);
	list.add(8);
	list.add(22);
	assert(list.size() == 7);
	list.filter(Condition2);
	assert(list.size() == 5);
	assert(list.getElement(0) == 2);
	assert(list.getElement(1) == 8);
	assert(list.getElement(2) == 10);
	assert(list.getElement(3) == 22);
	assert(list.getElement(4) == 56); // Check that all even elements are kept

	list.add(5);
	list.filter(Condition1);
	assert(list.size() == 4);
	ListIterator it = list.iterator();
	it.first(); // Start from the first element
	assert(it.getCurrent() == 2); // Check the first element
	assert(it.valid());
	while (it.valid()) {
		TComp current = it.getCurrent();
		assert(current <= 10); // Check that all elements are smaller than 10
		it.next();
	}

	std::cout << "Filter test passed!" << std::endl;
}


int main(){
	test_filter();
    testAll();
    testAllExtended();
    std::cout<<"Finished IL Tests!"<<std::endl;
	system("pause");
}