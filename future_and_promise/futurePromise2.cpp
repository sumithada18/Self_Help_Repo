#include "common.h"
#include "futurePromise.h"

// The producer's task function takes a std::promise as argument
void produce(std::promise<int>&prom) 
{
	
	// produce the result
	int x = 10;
	std::this_thread::sleep_for(2s);

	std::cout << "promise sets shared state to " << x << "\n";

	prom.set_value(x);
}

// The consumer's task function takes an std::future as argument
void consume(std::future<int>&fut) 
{

	// get the result from the 
	std::cout << "future calling get()... \n";
	int x = fut.get();
	std::cout << "future returns from calling get() \n";
	std::cout << "the data is: " << x << "\n";
}


// example 2 
void give(std::promise<double>& p)
{
    std::cout << "give thread calculating value \n";
	double piVal = 22.0 / 7;
    std::this_thread::sleep_for(2s);

    std::cout << "give thread sets the value! \n";
    p.set_value(piVal);
}

void take()
{
    std::promise<double>prom;
    std::future<double>fut = prom.get_future();
    std::thread child(give, std::ref(prom));
    std::cout << "take thread waiting to take the value.. \n";
    double val = fut.get();
    std::cout << "take took the val, it is: " << val;
    child.join();
}