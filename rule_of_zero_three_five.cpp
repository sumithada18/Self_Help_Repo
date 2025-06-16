The Core Problem: Who Owns the Resource?
The entire issue revolves around classes that manage a resource. A "resource" is anything that must be acquired and released, like:

- Memory allocated with new (the classic example).
- A file handle opened with fopen().
- A network socket.
- A database connection.

The C++ compiler is great at managing the lifetime of class members, but it knows nothing about these external resources. Its default behavior can lead to disaster.

  
  The Rule of Three (The C++98 Way)
This was the original rule for resource-managing classes. It states:

=> If a class needs a user-defined destructor, a copy constructor, or a copy assignment operator, it almost certainly needs all three.

The Logic (A Domino Effect):
1. The Trigger (The Destructor): You start by managing a raw pointer. To prevent a memory leak, you write a custom destructor to call delete.
  class MyString {
private:
    char* m_data;
public:
    // You write this to prevent a memory leak.
    ~MyString() {
        delete[] m_data;
    }
};
2. The First Domino (The Copy Constructor): Now, what happens when an object of your class is copied?
MyString s2 = s1;

The compiler's default copy constructor will perform a shallow copy. It just copies the value of the pointer m_data. Now both s1 and s2 point to the 
exact same memory. When s2 goes out of scope, its destructor deletes the data. When s1 goes out of scope later, its destructor tries to delete the 
same already-deleted memory. This is a double free, and your program will crash.

The Fix: You must write your own copy constructor that performs a deep copy: it allocates new memory for the copy and copies the content over.

3. The Second Domino (The Copy Assignment Operator): The exact same problem happens with assignment: s2 = s1;. The default assignment operator
   also does a shallow copy, leading to a double free.
  
The Fix: You must also write your own copy assignment operator to perform a deep copy.
This is the Rule of Three. The need for one of them triggers the need for all of them.

  
The Rule of Five (The C++11 Way)
C++11 introduced move semantics to avoid expensive copies for temporary objects. This added two new special member functions: the move 
constructor and the move assignment operator.
The rule became:

=> If you write any of the five special member functions, you should think about all five.

The Logic (The Performance Problem):
If you follow the Rule of Three and define a destructor, copy constructor, and copy assignment operator, the compiler makes a safe 
assumption: "This class is doing complex resource management. I will disable the automatic generation of move operations to avoid breaking anything."

What's the consequence? Your class, which could be efficiently moved, will now be slowly copied everywhere. For example, when a
std::vector<MyString> needs to resize, it will make expensive copies of every element instead of just quickly moving them

The Fix: To get both safety and performance, you must now implement all five:
-> The original three (destructor, copy ctor, copy assignment).
-> Move Constructor: Steals the pointer from the temporary source object and nulls out the source's pointer. This is very fast.
-> Move Assignment Operator: Does the same "stealing" for assignment.
This ensures your class is both correct when copied and efficient when moved.

The Rule of Zero (The Modern C++ Goal)
The Rule of Five is a lot of boilerplate code that's easy to get wrong. The modern C++ philosophy is that the best way to manage resources is to not manage them at all.
The rule is simple:

=> Classes that have custom destructors, copy/move constructors, or copy/move assignment operators should be rare. A class should 
   have to deal with zero resources directly.

The Logic (Delegation):
Instead of using raw pointers and managing resources yourself, you delegate that responsibility to classes that are already experts at it.
-> Instead of char*, use std::string.
-> Instead of T*, use std::unique_ptr<T> (for unique ownership) or std::shared_ptr<T> (for shared ownership).
-> Instead of a C-style array T[], use std::vector<T>.
These standard library classes already obey the Rule of Five perfectly. They know how to copy, move, and destroy themselves correctly.

The Result:
Your class now just contains these smart, resource-managing objects.

class MyModernString {
private:
    std::string m_data; // Let std::string manage the memory.
};
// That's it. You are done.

- Destructor? Not needed. m_data will destroy itself correctly.
- Copy Constructor? Not needed. The compiler's default version will call std::string's copy constructor, which does the right thing.
- Move Semantics? Not needed. The compiler's default versions will call std::string's move operations, which are highly efficient.
By not managing any resources yourself, you need to write zero special member functions. This is the Rule of Zero. It is the preferred, 
safest, and simplest approach in modern C++.
