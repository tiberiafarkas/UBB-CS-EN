#include <iostream>

using namespace std;

class Ex1 {
public:
    Ex1() {
        cout << "Exception1 ";
    }
    Ex1(const Ex1& ex) {
        cout << "Copy_ex1";
    }
};

class Ex2 : public Ex1 {
public:
    Ex2() {
        cout << "Exception2 ";
    }
    Ex2(const Ex2& ex) {
        cout << "Copy_exc2";
    }
};

class Ex3 : public Ex2 {
public:
    Ex3() {
        cout << "Ex3";
    }

};

void except(int x) {
    if (x < 0)
        throw Ex1{};
    else if (x == 0)
        throw Ex2{};
    cout << "Done";
}

int main()
{
    Ex3 a;

    try {
        cout << "Start ";
        try {
            except(0); //Exception1 Exception2 because it triggers both the constructors
        }
        catch (Ex1& e) {} //it matches because Ex2 is derived from Ex1
        except(-2); //Exception1
    } 
    catch (Ex1 e) {} //Copy_ex1

    //output:
    //Start Exception1 Exception2 Exception1 Copy_ex1
    return 0;
}
