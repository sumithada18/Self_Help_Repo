#include <iostream>
#include <thread>
#include <mutex>

// 100% thread-safe singleton example
class Singleton {
private:
	Singleton() {
		std::cout << "Cons.. called\n";
	}
public:
	int data = 10;
	static Singleton& getInstance() {
		// Guaranteed thread-safe in C++11 and above
		static Singleton instance;
		return instance;
	}
	void show() {
		std::cout << data << "\n";
	}
};
/*
The C++11 standard (and later) guarantees it.
1. First Time: The very first thread to reach static Singleton instance; will create and fully initialize it.
2. Other Threads Wait: If other threads arrive while it's being initialized, they automatically wait (the compiler/runtime handles this, often with hidden locks).
3. Safe Access: Once initialized, all threads safely get the same, single, fully-formed instance.
*/

void accessSingleton() {
	Singleton& s = Singleton::getInstance();
	s.show();
}

int main() {
	// Create multiple threads to access Singleton
	std::thread t1(accessSingleton);
	std::thread t2(accessSingleton);
	std::thread t3(accessSingleton);

	t1.join();
	t2.join();
	t3.join();

	return 0;
}
/*
1. Pointer to Heap Object Singleton:
• How it works: getInstance() does new Singleton (once) and stores the pointer. You get back this Singleton*.
• Memory: Object lives on the heap.
• Lifetime: You are (often implicitly) responsible for deleteing it. If not deleted, it's a memory leak. If deleted too early or multiple times, it's a crash.
• Thread-Safety (for creation): You need to manually add locks (like std::mutex with double-checked locking) to make getInstance() thread-safe.
• Access: singleton_ptr->memberFunction();

2. Static Local Object (by Reference) Singleton:
• How it works: getInstance() has static Singleton instance; inside. You get back a Singleton& (reference) to this instance.
• Memory: Object lives in static storage (like a global, but initialized on first use).
• Lifetime: Automatically managed. Created on first call to getInstance(), destroyed when the program ends. No manual delete needed.
• Thread-Safety (for creation): Guaranteed thread-safe in C++11 and later by the language itself. No manual locks needed for its creation.
• Access: singleton_ref.memberFunction();

Key Distinction:
• Pointer/Heap: Manual memory management (riskier), manual thread-safety for creation.
• Static/Reference: Automatic memory management (safer), automatic thread-safety for creation (C++11+).

**The static local reference version is generally preferred in modern C++ for its simplicity and safety.**
*/
