The Problem with NULL
NULL is an old C-style macro, usually defined as the integer 0. This creates ambiguity because the compiler can't tell if you mean the 
number 0 or a null pointer.

The Solution with nullptr
nullptr is a modern C++11 keyword. It has its own unique type (std::nullptr_t) that is not an integer. It can only be converted to a 
pointer type, never to int. This removes all ambiguity.

When to Care (The Core Example)
This ambiguity becomes a real problem with function overloading.
//========================================================================================================
  
void process(int value) { /* Process a number */ }
void process(char* ptr) { /* Process a pointer */ }

int main() {
    // The compiler sees NULL as 0 and calls the wrong function!
    process(NULL);      // Calls process(int)

    // The compiler knows nullptr is a pointer and calls the correct function.
    process(nullptr);   // Calls process(char*)
}

//========================================================================================================
The Simple Rule
In modern C++, always use nullptr. Never use NULL. It is safer, clearer, and avoids bugs


Real Example of Ambiguity:-
Imagine you have two functions to log a message: one for logging a numeric code, and one for logging a C-style string pointer.
  #include <iostream>

void log_message(int error_code) {
    std::cout << "Logged numeric code: " << error_code << std::endl;
}

void log_message(const char* message) {
    if (message)
        std::cout << "Logged string: " << message << std::endl;
    else
        std::cout << "Logged a null pointer message." << std::endl;
}

int main() {
    // You INTEND to call the pointer version with a null pointer.
    // But NULL is just the integer 0.
    log_message(NULL);
}

Output:
Logged numeric code: 0

This is the ambiguity: you meant to pass a null pointer, but because NULL is just an int, the compiler called the wrong function.
If you had used log_message(nullptr), it would have correctly called the pointer version.
