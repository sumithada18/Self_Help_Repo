//==============================================================================
// cenario: Converting a pointer to an integer to store it, then back.
// (Imagine you need to pass a pointer through an old C API that only accepts an integer type, 
// or store it in a data structure that only holds integers).
//==============================================================================

#include <iostream>
#include <cstdint> // For uintptr_t

struct MyData { int val = 42; };

// Simulate an old C API function that takes an integer "handle"
void process_handle(uintptr_t handle) {
    // In a real scenario, this C API would do something with the handle.
    // Here, we'll cast it back to see the data.
    MyData* data_ptr = reinterpret_cast<MyData*>(handle);
    std::cout << "Data via handle: " << data_ptr->val << std::endl;
}

int main() {
    MyData data_obj;
    MyData* original_ptr = &data_obj;

    // 1. Convert pointer to an integer type
    //    static_cast CANNOT do this pointer-to-integer directly.
    //    C-style cast COULD, but reinterpret_cast is more explicit for this specific intent.
    uintptr_t handle = reinterpret_cast<uintptr_t>(original_ptr);

    std::cout << "Original pointer address: " << original_ptr << std::endl;
    std::cout << "Integer handle: " << handle << std::endl;

    // Pass the integer "handle" to the API
    process_handle(handle);

    // 2. To get it back in C++ (if not done by the API):
    // MyData* retrieved_ptr = static_cast<MyData*>(handle); // COMPILE ERROR: static_cast cannot convert integer to pointer
    MyData* retrieved_ptr = reinterpret_cast<MyData*>(handle);

    if (retrieved_ptr == original_ptr) {
        std::cout << "Pointers match after conversion: " << retrieved_ptr->val << std::endl;
    }

    return 0;
}
/*

Why reinterpret_cast is key here:
 -  Pointer to uintptr_t: static_cast cannot directly convert a MyData* to uintptr_t. reinterpret_cast is 
    specifically designed for this kind of bit-pattern reinterpretation. A C-style cast (uintptr_t)original_ptr would also work, 
    but reinterpret_cast is more explicit about the low-level nature.
 -  uintptr_t to Pointer: Similarly, static_cast cannot convert an integer type like uintptr_t back to MyData*. reinterpret_cast is required.
 
Why it's the "only" C++ cast option:
 -  static_cast: Doesn't allow arbitrary pointer-to-integer or integer-to-pointer conversions (except for void* to integer in some contexts, 
    which isn't this case).
 -  const_cast: Only deals with const/volatile.
 -  dynamic_cast: Only for polymorphic class hierarchy navigation.
 
This example demonstrates a common low-level pattern. uintptr_t (or intptr_t) are integer types specifically defined in <cstdint> to
be capable of holding a pointer value without loss, making such conversions "safer" than using a generic int or long.

*/