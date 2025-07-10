#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

//define the classes Complex and Vector such that the following C++ code is correct and \
its results are the ones indicated in the comments

class Complex {
private:
    int re, im;
public:
    Complex() {
        re = 0;
        im = 0;
    };
    Complex(int a, int b) {
        re = a;
        im = b;
    }
    Complex(const Complex& z) {
        re = z.re;
        im = z.im;
    }
    int getReal() {
        return re;
    }
    int getImaginary() {
        return im;
    }
    bool operator==(Complex& a) {
        return ((a.re == re) && (a.im == im));
    }
    Complex& operator/(int a) {
        if (a == 0)
            throw runtime_error("Division by zero!");

        Complex z(re, im);
        z.re /= a;
        z.im /= a;
        return z;
    }
    friend ostream& operator<<(ostream& os, Complex& a) {
        os << a.re << "+" << a.im << "i";
        return os;
    }
};

template<typename T>
class Vector {
    vector<T> ceva;
public:
    Vector(vector<T> v) {
        ceva = v;
    }
    void printAll(ostream& os) {
        for (auto i : ceva) {
            os << i << ", ";
        }
    }
};

void complex() {
    Complex a{}, b{ 1,2 }, c{ 6,4 }, d{ b };
    assert(a.getReal() == 0 && a.getImaginary() == 0);
    assert(c.getImaginary() == 4);
    assert(b == d);
    Complex res1 = c / 2;
    cout << res1 << '\n'; //prints: 3+2i
    try {
        Complex res2 = b / 0;
    }
    catch (runtime_error& e) {
        assert(strcmp(e.what(), "Division by zero!") == 0);
    }

    Vector<string> v1{ vector<string>{"hello", "bye"} };
    v1.printAll(std::cout); //prints: hello, bye
    
    Vector<Complex> v2{ vector<Complex>{a, b, c, d} };
    v2.printAll(std::cout); //prints: 0+0i, 1+2i, 6+4i, 1+2i
}

int main()
{
    complex();
}

