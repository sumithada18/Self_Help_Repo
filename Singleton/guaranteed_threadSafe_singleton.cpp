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
