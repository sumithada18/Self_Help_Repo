#include <iostream>
#include <atomic> // For thread-safe ID counter

/*
--------------------------------------------------------------------------------
Problem Statement & Solution: System-Wide Unique ID Generator
--------------------------------------------------------------------------------
Problem:
Need to generate identifiers that are unique across an application.
Independent ID generation can lead to collisions.

Solution using Singleton:
A Singleton `UniqueIDGenerator` acts as a single, central source.
1.  Ensures only one ID generator instance.
2.  Provides global access via `getInstance()`.
3.  Maintains state (e.g., a counter) for unique ID dispensation.
--------------------------------------------------------------------------------
*/

class UniqueIDGenerator {
private:
    // Private constructor: Only getInstance() can call this.
    UniqueIDGenerator() : next_id_(1) { /* std::cout << "ID Gen created\n"; */ }

    // Disallow copying/moving to ensure one instance.
    UniqueIDGenerator(const UniqueIDGenerator&) = delete;
    UniqueIDGenerator& operator=(const UniqueIDGenerator&) = delete;

    std::atomic<long long> next_id_; // Thread-safe counter for IDs.

public:
    // Public static method to get the single instance.
    // C++11+ ensures thread-safe initialization of static local 'instance'.
    static UniqueIDGenerator& getInstance() {
        static UniqueIDGenerator instance; // Created once, on first call.
        return instance;
    }

    // Generates and returns a new unique ID.
    long long generateID() {
        return next_id_++; // Atomically increments and returns old value.
    }
};

int main() {
    // Get the singleton instance
    UniqueIDGenerator& generator = UniqueIDGenerator::getInstance();

    // Generate some IDs
    std::cout << "ID 1: " << generator.generateID() << std::endl;
    std::cout << "ID 2: " << generator.generateID() << std::endl;

    // Getting instance again gives the same object
    UniqueIDGenerator& another_ref_to_generator = UniqueIDGenerator::getInstance();
    std::cout << "ID 3 (via another_ref): " << another_ref_to_generator.generateID() << std::endl;

    return 0;
}

/*
--------------------------------------------------------------------------------
Key Explanation Points (for last-minute revision):
--------------------------------------------------------------------------------
1.  **Core Idea:** `UniqueIDGenerator` provides unique numbers system-wide.
2.  **Singleton Why:** Ensures only *one* ID sequence exists, preventing duplicate IDs.
3.  **How it Works (Minimal):**
    *   `private UniqueIDGenerator()`: Prevents direct creation.
    *   `static UniqueIDGenerator& getInstance()`: The only way to get it. Uses a `static` local variable, so it's created once and safely (C++11+).
    *   `generateID()`: Gives the next ID using a thread-safe `std::atomic` counter.
4.  **Benefit:** Centralized, safe, and simple way to get unique IDs anywhere in the app.
--------------------------------------------------------------------------------
*/
