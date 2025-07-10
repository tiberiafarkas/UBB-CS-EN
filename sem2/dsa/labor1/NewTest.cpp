#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <stdio.h>
#include <assert.h>

void testRemoveCurrent() {
    FixedCapBiMap m(10);

    // Add elements to the map
    assert(m.isEmpty() == true);
    assert(m.size() == 0); //add elements
    assert(m.add(5, 5) == true);		//+5
    assert(m.add(1, 111) == true);		//+111
    assert(m.add(10, 110) == true);	//+110
    assert(m.add(7, 7) == true);		//+7
    assert(m.add(1, 1) == true); // this is the second value for key 1   +1
    assert(m.add(1, 3) == false); // we cannot add a third value
    assert(m.add(10, 10) == true);	// this is the second value for key 10  +10
    assert(m.add(-3, -3) == true);		//+(-3)
    assert(m.size() == 7);

    // Initialize an iterator
    FixedCapBiMapIterator it = m.iterator();

    // Move iterator to the second element
	it.next();

    // Remove current element
	TElem removed = it.removeCurrent();
    assert(removed.first == 1 && removed.second == 111);

	// Check the size of the map
	assert(m.size() == 6);

    // Reset iterator and check remaining elements
	it.first();
    int sum1 = 0, sum2 = 0;
    while (it.valid()) {
        TElem e = it.getCurrent();
        sum1 += e.first;
        sum2 += e.second;
		it.next();
    }


    // Expected sum calculation after removal
    assert(sum1 == 30); // 5 + 10 + 7 + 1 + 10 + (-3) = 30
    assert(sum2 == 130); // Previous sum was 240

    printf("testRemoveCurrent passed!\n");
}
