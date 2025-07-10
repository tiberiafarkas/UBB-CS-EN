#include <iostream>

using namespace std;

class Vector {
    int* elems;
    int size;

public:
    Vector() : size{ 0 } {
        elems = new int[10];
    }
    void add(int elem) {
        elems[size++] = elem;
    }
    int& operator[](int pos) {
        if (pos < 0 || pos >= size)
            throw runtime_error{ "Index out of bounds." };
        return elems[pos];
    }
    ~Vector() {
        delete[] elems;
    }
};

int main()
{
    Vector v1;
    v1.add(0);
    v1.add(1);
    Vector v2 = v1; //This invokes the default copy constructor, which performs a shallow copy:\
    v2.size = v1.size = 2\
    v2.elems = v1.elems => both point to the same memory!
    
    try {
        v1[0] = 2; //it also changes in v2
        cout << v1[0] << " " << v1[1] << " "; //2 1
        cout << v2[0] << " " << v2[1] << " "; //2 1
    }
    catch (runtime_error& e) {
        cout << e.what();
    }
    return 0;
    //because both v1 and v2 have destructors, when they go out of scope, both try
    //to delete elems, leading to a double delete and an undefined behavior
    //you can fix it by implementing a copy constructor
}
