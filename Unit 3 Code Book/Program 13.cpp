/*
 * Unit 3 Code Book
 * Concept 13: Virtual Destructor
 * Aim: To demonstrate correct destruction of a derived object through a base pointer.
 */

#include <iostream>

class Base {
public:
    virtual ~Base() {
        std::cout << "Base destructor\n";
    }
};

class Derived : public Base {
public:
    ~Derived() override {
        std::cout << "Derived destructor\n";
    }
};

int main() {
    Base* pointer = new Derived();
    delete pointer;
    return 0;
}
