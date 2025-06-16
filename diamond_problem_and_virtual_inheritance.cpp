=>  Before Virtual Inheritance (Ambiguity)
#include <iostream>
class base {
public:
    int x;
};

class derived1 : public base {};
class derived2 : public base {};

// ⚠️ Diamond: 2 copies of 'base'
class super_derived : public derived1, public derived2 {
public:
    void show() {
        // std::cout << x; // ❌ Error: Ambiguous
        std::cout << derived1::x; // ✅ Need to specify path
    }
};


=> After Virtual Inheritance (Single Shared base)
#include <iostream>
class base {
public:
    int x;
};

class derived1 : virtual public base {};
class derived2 : virtual public base {};

// ✅ Only 1 shared 'base' instance
class super_derived : public derived1, public derived2 {
public:
    void show() {
        std::cout << x; // ✅ No ambiguity
    }
};


After Virtual Inheritance: The "Shared Section with Pointers" Layout
Virtual inheritance completely changes the rules of object layout. It introduces a level of indirection.
1. When you define class Derived1 : virtual public Base, you are telling the compiler: "Do not embed the Base subobject directly inside me. 
   Instead, include a hidden pointer (a virtual base pointer or vbptr). This pointer will tell me where to find the Base subobject at runtime."
   Derived2 does the same.
2. Now, the responsibility shifts. The job of creating the Base subobject no longer belongs to Derived1 or Derived2. It becomes the responsibility of
   the most-derived class—in this case, SuperDerived.
3. When a SuperDerived object is created, here is the new memory layout:
- First, it creates one single, shared Base subobject.
- Then, it adds the Derived1 specific members and Derived2 specific members.
- Crucially, it sets the hidden vbptr inside the Derived1 part to point to the shared Base subobject.
- It also sets the hidden vbptr inside the Derived2 part to point to that same shared Base subobject.


1. Base
The simplest case. It's just its own data.
+---------------+
| Base members  |
+---------------+

2. Derived1 (When created as a standalone object)
Since it's the "most-derived", the compiler can optimize. It just embeds Base.
+--------------------------+
|      Base subobject      |
+--------------------------+
|   Derived1's own members |
+--------------------------+

3. SuperDerived (The complete picture with virtual)
This is where the layout changes fundamentally.
+-------------------------------------------------+  <-- Start of SuperDerived object
|          Single, Shared BASE subobject          |
+-------------------------------------------------+
|   Derived1's own members                        |
|   +--------------------------+                  |
|   | HIDDEN POINTER (vbptr)   | --> points back up to the shared Base
|   +--------------------------+                  |
|   | Other Derived1 members...|                  |
+-------------------------------------------------+
|   Derived2's own members                        |
|   +--------------------------+                  |
|   | HIDDEN POINTER (vbptr)   | --> points back up to the same shared Base
|   +--------------------------+                  |
|   | Other Derived2 members...|                  |
+-------------------------------------------------+
|   SuperDerived's own members                    |
+-------------------------------------------------+

   Virtual inheritance exists for one reason and one reason only: to solve the Diamond Problem. You should never use it unless
you have this specific multiple inheritance scenario.
