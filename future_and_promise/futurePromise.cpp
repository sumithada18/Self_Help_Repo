#include "common.h"
#include "futurePromise.h"
// a very simple example

void task(std::promise<int>& p) {
    int x = 42;
    std::this_thread::sleep_for(1s);
    p.set_value(x);
}
// Time 	Main Thread	                    Worker Thread (task)
// T0	Create promise & future.	            -
// T1	Starts thread task.	                Picks reference to promise.
// T2	Calls fut.get() (blocks, waits).	Sleeps for 1 second (sleep_for).
// T3	(Still waiting for value).	        Wakes up, sets promise.set_value(42).
// T4	future.get() receives value 42.	    Finishes execution.
// T5	Prints data is: 42.	                Thread joins back.