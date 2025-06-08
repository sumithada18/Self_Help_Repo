#include "common.h"
#include "futurePromise.h"

int main() {
	// example 1
	/*
	std::promise<int>prom;
	std::future<int>fut = prom.get_future();

	std::thread thr(task, std::ref(prom));
	int x = fut.get();

	std::cout << "data: " << x << "\n";

	thr.join();
	*/


	// example 2
	/*
	std::promise<int>prom;

	// Get the future associated with the promise
	std::future<int>fut = prom.get_future();

	// Start the threads
	// The producer task function takes the promise as argument
	std::thread t_producer(produce, std::ref(prom));

	// The consumer task function takes the future as argument
	std::thread t_consumer(consume, std::ref(fut));

	t_producer.join();
	t_consumer.join();
	*/

	// example 3
	/*
	std::thread t(take);
	t.join();
	*/

	// example 4: storing exception in the shared state
	std::promise<int>p;
	std::future<int>f = p.get_future();
	std::thread t_producer(promise_exception_ptr::produce, std::ref(p));
	std::thread t_consumer(promise_exception_ptr::consume, std::ref(f));
	t_producer.join();
	t_consumer.join();

	return 0;
}