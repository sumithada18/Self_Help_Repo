#include <exception>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>
#include <memory>
/*
🔒 RAII(Resource Acquisition Is Initialization)
What it is :
    Binds a resource’s lifetime to an object’s lifetime.
Goal :
    Ensure resources are acquired in constructor and released in destructor.

    ✅ RAII Guarantees
     - Resource always available while object is alive.
     - Resource released automatically when object goes out of scope(even on exception).
     - Destruction happens in reverse order of construction.
     - Exception safety via stack unwinding.

    📦 RAII Summary
    - Wrap resource in a class :
        - Constructor → acquires resource or throws.
        - Destructor → releases resource(never throws).
    - Use on stack(automatic or temporary objects).

    ⚙️ Common Resources Managed by RAII
    - Heap memory
    - Files
    - Mutexes
    - Sockets
    - Threads
    - DB connections

    
📚 Standard Library RAII Examples
=> std::string, std::vector, std::jthread(C++20)
=> Smart pointers :
    std::unique_ptr, std::shared_ptr via make_unique, make_shared
=> Mutex wrappers :
    std::lock_guard, std::unique_lock, std::shared_lock

⚠️ RAII Doesn't Apply To
 => Resources not acquired before use, e.g. :
  - CPU time
  - Cache
  - Bandwidth
  - Power
  - Stack memory
*/

// ======== Example 1: Heap Memory Management ========
// Without RAII - memory leak on exception
void no_raii_memory() {
    int* data = new int[5];
    throw std::runtime_error("Error!"); // 'delete' never reached
    delete[] data; // ❌ Never executed
}

// With RAII - using std::unique_ptr
void with_raii_memory() {
    std::unique_ptr<int[]> data(new int[5]);
    throw std::runtime_error("Error!"); // ✅ Memory auto-freed
}



// ======== Example 2: File Handling ========
// Without RAII - file left open if early return
void no_raii_file() {
    FILE* f = fopen("test.txt", "r");
    // what if test is not there ?
    auto customDeleter = [](FILE* f) {
        // 
        fclose(f);
        };
    std::unique_ptr<FILE, decltype(customDeleter)>ptr(f, customDeleter);
    if (!f) return;
    return; // ❌ forgot fclose — file left open
    fclose(f);
    // frees heap memory
}

// With RAII - using std::ifstream
void with_raii_file() {
    std::ifstream file("test.txt");
    if (!file) return; // ✅ auto-closes on exit
}



// ======== Example 3: Mutex Lock ========
// Without RAII - forgot to unlock
std::mutex m;
void no_raii_mutex() {
    m.lock();
    throw std::runtime_error("Crash!"); // ❌ never unlocked
    m.unlock();
}

// With RAII - std::lock_guard
void with_raii_mutex() {
    std::lock_guard<std::mutex> lock(m); // ✅ auto-unlock on scope exit
    throw std::runtime_error("Crash!");
}
// ---
