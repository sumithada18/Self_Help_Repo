#include <iostream>
#include <thread>
#include <mutex>
/*
class Singleton {
private:
    static Singleton* instance;

    Singleton() {
        std::cout << "Constructor called by thread: "
                  << std::this_thread::get_id() << "\n";
    }

public:
    // Prevent copy and assignment
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* getInstance() {
        // Not thread-safe: multiple threads can create multiple instances
        if (!instance)
            instance = new Singleton;
        return instance;
    }

    void show() {
        std::cout << "Instance address: " << this
                  << " | Thread ID: " << std::this_thread::get_id() << "\n";
    }
};

// Initialize static member
Singleton* Singleton::instance = nullptr;

void accessSingleton() {
    Singleton* s = Singleton::getInstance();
    s->show();
}
*/


// This is bette than the above thread unsafe code
// This is thread safe but not 100%
#include <iostream>
#include <mutex>
#include <thread>

std::mutex m;

class Singleton {
private:
	static Singleton* instance;

	Singleton() {
		std::cout << "Constructor called by thread: "
		          << std::this_thread::get_id() << "\n";
	}

public:
	// Prevent copy and assignment
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	static Singleton* getInstance() {
		// First check (not locked): Improves performance
		if (!instance) {
			std::lock_guard<std::mutex> lock_g(m); // Lock acquired

			// Second check (locked): Avoids creating multiple instances
			if (!instance)
				instance = new Singleton; // Not 100% safe due to potential instruction reordering
		}
		return instance;
	}
	/*
	instance = new Singleton; is not atomic:

	1. Allocate memory
	2. Construct Singleton object
	3. Assign address to instance
	Compiler/CPU can reorder (e.g., steps 3 before 2), so another thread might see instance != nullptr and return a partially constructed object - leading to undefined behavior.
	*/

	void show() {
		std::cout << "Instance address: " << this
		          << " | Thread ID: " << std::this_thread::get_id() << "\n";
	}
};

// Initialize static member
Singleton* Singleton::instance = nullptr;


void accessSingleton() {
	Singleton* s = Singleton::getInstance();
	s->show();
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
