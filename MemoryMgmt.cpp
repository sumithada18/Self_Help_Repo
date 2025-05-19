#include <iostream>

class myClass {
public:
	myClass() {
		std::cout << "cons.. called\n";
	}
	~myClass() {
		std::cout << "des.. called\n";
	}
};

int main()
{
	myClass* obj = new myClass;
	free(obj);

	//Should we do this?
	// Absolutely NOT. It's undefined behavior and a guaranteed way to cause resource leaks and potential crashes.

	/*
	What would happen?
	=> new MyClass() does two main things:
	 - Calls operator new(sizeof(MyClass)) to allocate raw memory. Under the hood, operator new might use malloc, but it's not guaranteed. It could use a completely different memory management system.
	 - Calls the MyClass constructor on that allocated memory.
	 
	=> free(obj) does one main thing:
	 - It attempts to deallocate the memory block pointed to by obj. free expects this memory to have been allocated by malloc (or calloc, realloc).
	Possible Problems:
	 - Destructor Not Called (Most Critical): free() knows nothing about C++ objects or destructors. The destructor MyClass::~MyClass() will not be called.
	 If MyClass manages any resources (e.g., other dynamically allocated memory, file handles, mutexes), those resources will leak.
	 - Heap Corruption (Potential):
	If operator new and malloc/free use different underlying heap managers, calling free on memory allocated by new is undefined behavior and can corrupt the heap.
	Even if operator new does use malloc internally, it might add its own bookkeeping information (e.g., for debugging, alignment, or new[] metadata) around the memory block. 
	free won't understand this extra information and might misinterpret it, leading to heap corruption (e.g., corrupting free lists, adjacent memory blocks).
	*/
	return 0;
}
