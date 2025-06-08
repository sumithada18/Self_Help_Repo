#include "common.h"
#include "futurePromise.h"

namespace promise_exception
{
    // the producer's task function takes a std::promise as arguement 
    void produce(std::promise<int>& p)
    {
        try {
            int x = 12;
            std::this_thread::sleep_for(2s);

            // code may throw exception
            if (1) throw std::out_of_range("oops");

            // if no exception - stores the result in the shared state
            std::cout << "proimse sets shared state to " << x << "\n";
            p.set_value(x);
        }
        catch (...) {
            // Exception thrown - store it in the shared state
            p.set_exception(std::current_exception());
        }
    }

    // the consumer's task function takes std::future as argument 
    void consume(std::future<int>& f)
    {
        try {
            // get the result from the shared state - may throw 
            int x = f.get();
            std::cout << "future returns from calling get() \n";
            std::cout << "the answer is: " << x << std::endl;
        }
        catch (std::exception& e) {
            // exception thrown - get it from the shared state
            std::cout << "exception caught: " << e.what() << "\n";
        }
    }
}

namespace promise_exception_ptr {

	void produce(std::promise<int>& p) {
        int x = 12;
        if (1) {
            p.set_exception(std::make_exception_ptr(std::out_of_range("oops")));
            return;
        }
        p.set_value(x);
	}
	void consume(std::future<int>& f) {
        try {
            int x = f.get();
        }
        catch (std::exception& e) {
            std::cout << "exception caught! : " << e.what() << "\n";
        }
	}
}

// exception_ptr    -   A type - safe object storing an exception(not raw pointer).
// set_exception()  -   Stores the exception_ptr in shared state.
// future.get()     -   If shared state holds an exception, it rethrows it!

/*
 If using throw in a try-catch block:
-> Use std::current_exception() to capture the exception and pass to set_exception().

 If you want to create and pass an exception directly (without throw):
-> Use std::make_exception_ptr() to create the exception pointer and pass to set_exception().
*/