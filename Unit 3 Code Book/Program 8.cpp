/*
 * Unit 3 Code Book
 * Concept 8: Base Pointer Without a Virtual Function
 * Aim: To observe static binding when a base function is not virtual.
 */

#include <iostream>

class Base {
public:
    void display() const {
        std::cout << "Base display function\n";
    }
};

class Derived : public Base {
public:
    void display() const {
        std::cout << "Derived display function\n";
    }
};

int main() {
    Derived derivedObject;
    Base* basePointer = &derivedObject;
    basePointer->display();
    return 0;
}
