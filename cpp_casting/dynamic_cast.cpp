#include <iostream>

class Base {
public:
    virtual void virtual_func() {
        // Required to make Base polymorphic
    }
};

class Derived : public Base {
public:
    void derived_func() {
        std::cout << "derived::func()\n";
    }
};

class AnotherDerived : public Base {
    // No additional members
};

int main() {
    // Using static_cast and no polymorphism is involved here
    Base* bptr = new AnotherDerived;

    // Derived* dptr = static_cast<Derived*>(bptr); // It compiles successfully
    /*
        It compiles because:
        1. static_cast performs a compile-time check.
        2. It sees you're trying to cast a Base* (b_ptr) to a Derived* (d_ptr_static).
        3. It checks if Derived is publicly inherited from Base (which it is).
        4. Because this inheritance relationship exists, static_cast allows the downcast,
           assuming you (the programmer) know it's safe. It doesn't know or check what b_ptr
           actually points to at runtime.
    */

    // dptr->derived_func(); // This may run, may not, but even if it runs, it is undefined behaviour.

    // Using dynamic_cast and making base class polymorphic
    Derived* dptr = dynamic_cast<Derived*>(bptr);
    if (dptr) {
        std::cout << "cast successful\n";
        // Now I can call the function
        dptr->derived_func();
    } else {
        std::cout << "cast unsuccessful, cannot call the desired func\n";
    }

    // Here's how many things would be happening internally:
    /*
        1. RTTI Prerequisite:
           Because Base is polymorphic (has a virtual function), objects of Base and its
           derived classes (like AnotherDerived and Derived) usually contain a hidden pointer
           (often called a vptr or virtual pointer). This vptr points to a vtable for that class.

        2. Accessing Type Information:
           - When dynamic_cast<Derived*>(b_ptr) is called, the runtime system uses b_ptr to find the object.
           - It then uses that object's vptr to access the vtable of the actual object (AnotherDerived's vtable).
           - The vtable contains RTTI (Run-Time Type Information) which describes the class and its hierarchy.

        3. The Check:
           - dynamic_cast knows the actual dynamic type of the object is AnotherDerived.
           - The cast target is Derived*.
           - It checks: "Is AnotherDerived the same as Derived, OR is it publicly derived from Derived?"

        4. The Decision:
           - RTTI system determines AnotherDerived is not Derived, nor derived from Derived.
           - The cast is invalid.

        5. Returning nullptr:
           - Since the cast is invalid, dynamic_cast returns nullptr when casting to a pointer.
    */

    return 0;
}
