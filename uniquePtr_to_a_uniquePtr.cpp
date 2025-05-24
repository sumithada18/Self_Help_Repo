#include <iostream>
#include <memory> // Required for std::unique_ptr, std::make_unique

class MyClass {
public:
    MyClass() {
        std::cout << "MyClass constructor called.\n";
    }

    virtual void hustle() {
        std::cout << "Hustle going on...\n";
    }

    ~MyClass() {
        std::cout << "MyClass destructor called.\n";
    }
};

int main() {
    std::cout << "--- Step 1: Create uptr ---" << std::endl;
    // uptr is an object (on the stack) that owns a MyClass object (on the heap).
    std::unique_ptr<MyClass> uptr = std::make_unique<MyClass>();
    // Memory:
    // Stack: uptr (contains raw_ptr_to_MyClass_instance_1)
    // Heap:  MyClass_instance_1

    std::cout << "\n--- Step 2: Create uptr2, moving from uptr ---" << std::endl;
    // uptr2 is an object (on the stack).
    // std::make_unique<std::unique_ptr<MyClass>>(std::move(uptr)) does two things:
    // 1. Allocates a std::unique_ptr<MyClass> object on the HEAP. Let's call this heap_inner_uptr_obj.
    // 2. Initializes this heap_inner_uptr_obj by moving from uptr.
    //    - heap_inner_uptr_obj now owns MyClass_instance_1.
    //    - uptr becomes null.
    // uptr2 now owns heap_inner_uptr_obj.
    std::unique_ptr<std::unique_ptr<MyClass>> uptr2 =
        std::make_unique<std::unique_ptr<MyClass>>(std::move(uptr));
    // Memory:
    // Stack: uptr  (contains nullptr)
    // Stack: uptr2 (contains raw_ptr_to_heap_inner_uptr_obj)
    // Heap:  heap_inner_uptr_obj (type: std::unique_ptr<MyClass>, contains raw_ptr_to_MyClass_instance_1)
    // Heap:  MyClass_instance_1

    std::cout << "\n--- Step 3: Check uptr ---" << std::endl;
    if (!uptr) {
        std::cout << "uptr is now null, as expected after move.\n";
    }

    std::cout << "\n--- Step 4: Access MyClass object via uptr2 ---" << std::endl;
    if (uptr2 && *uptr2) { // Check both pointers are valid
        // (*uptr2) dereferences uptr2. It gives a reference to the heap_inner_uptr_obj.
        // This heap_inner_uptr_obj is of type std::unique_ptr<MyClass>.
        // So, (*uptr2)->hustle() calls operator-> on heap_inner_uptr_obj,
        // which gets the raw pointer to MyClass_instance_1, then calls hustle().
        std::cout << "Calling hustle using (*uptr2)->hustle(): ";
        (*uptr2)->hustle();

        // Alternative:
        // (**uptr2) dereferences uptr2 to get heap_inner_uptr_obj,
        // then dereferences heap_inner_uptr_obj to get a reference to MyClass_instance_1.
        std::cout << "Calling hustle using (**uptr2).hustle(): ";
        (**uptr2).hustle();
    }

    std::cout << "\n--- End of main, destructors will be called ---" << std::endl;
    // Destruction order:
    // 1. uptr2 goes out of scope. Its destructor is called.
    //    - uptr2's destructor deletes the heap_inner_uptr_obj (the std::unique_ptr<MyClass> it owns).
    // 2. When heap_inner_uptr_obj is deleted, its destructor is called.
    //    - heap_inner_uptr_obj's destructor deletes the MyClass_instance_1 it owns.
    //    - MyClass destructor is called.
    // 3. uptr (which is null) goes out of scope. Its destructor does nothing.

    return 0;
}