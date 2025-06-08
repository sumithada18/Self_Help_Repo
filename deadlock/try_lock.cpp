#include <iostream>
#include <thread>
#include <mutex>
using namespace std::literals;

std::mutex m1, m2;

void taskA()
{
	std::unique_lock<std::mutex>ul1(m1, std::defer_lock);
	std::unique_lock<std::mutex>ul2(m2, std::defer_lock);

	printf("taskA trying to lock the mutexes \n");
	auto index = std::try_lock(ul1, ul2);
	if (index == -1) {
		std::cout << "taskA locked mutexes m1 and m2 \n";
		std::this_thread::sleep_for(50ms);
		std::cout << "taskA unlocking mutexes m1 and m2 \n";
	}
	else {
		std::cout << "unable to lock mutex: " << index << std::endl;
	}
}
void taskB()
{
	std::unique_lock<std::mutex>ul1(m2, std::defer_lock);
	std::unique_lock<std::mutex>ul2(m1, std::defer_lock);

	printf("taskB trying to lock the mutexes \n");
	auto index = std::try_lock(ul2, ul1);
	if (index == -1) {
		std::cout << "taskB locked mutexes m2 and m1 \n";
		std::this_thread::sleep_for(50ms);
		std::cout << "taskB unlocking mutexes m2 and m1 \n";
	}
	else {
		std::cout << "unable to lock mutex: " << index << std::endl;
	}
}

//The moment std::try_lock fails on any mutex,
//it immediately stops and returns the index of the mutex that couldn't be locked.

int main() {

	std::thread t1(taskA);
	std::thread t2(taskB);

	t1.join();
	t2.join();

	return 0;
}