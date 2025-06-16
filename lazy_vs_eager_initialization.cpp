1. Eager Initialization (Initialize Early)

-> What: An object or resource is created/initialized as soon as its defining scope is entered or when the program/class holding it starts up, regardless of whether it's immediately needed.
-> Analogy: You bake a cake first thing in the morning, even if the party isn't until the evening. The cake is ready whenever someone wants it.
-> Pros:
  - The object is always ready when needed; no delay at the point of first use.
  - Simpler to implement sometimes.
-> Cons:
  - Can waste resources (memory, time) if the object is never actually used.
  - Can slow down program startup if many objects are eagerly initialized.

Example Idea:

// Eager initialization of a global lookup table
std::map<std::string, int> config_values = loadConfigurationFile(); // Loaded at program start

class MySystem {
    HeavyResource resource_ = HeavyResource(); // Member initialized when MySystem is created
public:
    void useResource() { /* resource_ is already available */ }
};



2. Lazy Initialization (Initialize On-Demand)

-> What: An object or resource is created/initialized only the first time it is actually needed or requested.
-> Analogy: You only bake the cake when a guest specifically asks for cake.
-> Pros:
  - Saves resources if the object is never used.
  - Can improve startup time if initialization is expensive.
-> Cons:
  - The first time the object is accessed, there will be a delay while it's initialized.
  - Requires extra logic (e.g., a check) to see if it's already initialized.
  - Can be more complex to implement correctly, especially in multi-threaded environments (needs synchronization).

Example Idea (using a pointer and a check):

// Lazy initialization of a global connection
DatabaseConnection* g_db_connection = nullptr;

DatabaseConnection& getConnection() {
    if (g_db_connection == nullptr) {
        g_db_connection = new DatabaseConnection("connection_string"); // Initialized on first call
    }
    return *g_db_connection;
}

class MySystem {
    std::unique_ptr<HeavyResource> resource_ptr_ = nullptr;
public:
    HeavyResource& getResource() {
        if (!resource_ptr_) {
            resource_ptr_ = std::make_unique<HeavyResource>(); // Initialized on first call to getResource
        }
        return *resource_ptr_;
    }
};
(A common pattern for lazy static initialization in C++ is the "construct on first use idiom" using a static local variable within a function.)

When to Use Which:
-> Eager: Use for objects that are small, cheap to create, and very likely to be used, or when the delay of first-use initialization is unacceptable.
-> Lazy: Use for objects that are expensive to create, large, or may not be used at all, and when a slight delay on first access is acceptable, 
  or to speed up initial program/module loading.
