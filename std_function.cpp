Elaborated Understanding of std::function:
std::function is a versatile, type-safe class template in C++ (often referred to as a "wrapper") designed to store and invoke any kind of callable target.
=> When you instantiate std::function, you specify the signature (return type and parameter types) it will manage, for example, std::function<int(std::string, double)>.
=> It can indeed be instantiated without an initial callable, in which case it's in an "empty" or "null" state (calling it would throw std::bad_function_call). 
   This isn't "useless" as it allows for delayed assignment or optional callbacks.
=> Its core strength is that it can store various types of callables:
  - Regular function pointers
  - Lambda expressions (including those with captures)
  - Functors (objects of classes that overload operator())
  - Pointers to member functions (when bound to an object instance, often using std::bind or a lambda capture).
=> The critical requirement is that the signature of the callable being stored must be compatible with the signature specified for the std::function instance. 
   "Compatible" means it can be invoked with the arguments of the std::function's signature and its return type can be converted to the std::function's return type.
=> An instance of std::function is itself callable using the standard function call syntax (e.g., my_func(arg1, arg2)). This makes it seamless to use wherever a 
   function call is expected.
=> It can be easily passed to functions or APIs that expect a callable with a matching signature, providing great flexibility to the API designer and user.
=> Its "generic" nature stems from this ability to hold diverse callable types under a single, uniform std::function type (this is known as type erasure).
=> At any given time, a std::function instance holds at most one callable target.
=> It is reassignable: you can assign a new (and potentially different kind of) callable to an existing std::function object as many times as needed, as long 
   as the signature compatibility is maintained. Each assignment replaces the previously held callable.

=> When do we need it? (Key Use Cases)
  *   **Storing Callbacks:**
    *   When you need to store a callback in a variable or class member, and that callback could come from various sources (function, lambda, functor).
    ```c++
    std::function<void(int)> on_event_callback;
    on_event_callback = [](int x){ std::cout << "Event: " << x << std::endl; };
    on_event_callback(10);
    on_event_callback = some_global_function;
    ```

*   **Passing Callbacks to Functions:**
    *   When writing a function that needs to accept *any* callable matching a specific signature as a parameter.
    ```c++
    void process_data(const std::vector<int>& data, std::function<void(int)> process_item) {
        for (int item : data) {
            process_item(item);
        }
    }
    // process_data(my_vec, some_lambda_or_functor_or_func_ptr);
    ```

*   **Implementing Type-Erased Command Patterns or Strategy Patterns:**
    *   Store different "commands" or "strategies" (which are callable) in a collection of `std::function` objects.

*   **As Return Types (Less Common, but Possible):**
    *   A function can return a `std::function` if it needs to generate or select a callable at runtime.
