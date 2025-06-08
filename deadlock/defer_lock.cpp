//#include <iostream>
//#include <thread>
//#include <mutex>
//using namespace std::literals;
//
//std::mutex m1, m2;

//void task1() {
//	std::unique_lock<std::mutex>ul1(m1, std::defer_lock);
//	std::unique_lock<std::mutex>ul2(m2, std::defer_lock);
//
//	std::cout << "task1 tring to lock the mutexes \n";
//	std::lock(ul1, ul2);
//	std::cout << "task1 has locked mutexes 1 and 2 \n";
//
//	std::this_thread::sleep_for(50ms);
//
//	std::cout << "task1 is unlocking the mutexes \n";
//}

//void task2() {
//	std::unique_lock<std::mutex>ul1(m2, std::defer_lock);
//	std::unique_lock<std::mutex>ul2(m1, std::defer_lock);
//
//	std::cout << "task2 tring to lock the mutexes \n";
//	std::lock(ul1, ul2);
//	std::cout << "task2 has locked mutexes 1 and 2 \n";
//
//	std::this_thread::sleep_for(50ms);
//
//	std::cout << "task2 is unlocking the mutexes \n";
//}

//int main() {
//	std::thread t1(task1);
//	std::thread t2(task2);
//
//	t1.join();
//	t2.join();
//
//	return 0;
//}

/*
Real-World Use of std::lock + std::defer_lock:
Useful when a function needs to lock multiple resources, but you want to control exactly when locking happens and avoid deadlocks.
For example: multi-resource banking transactions, parallel logging, or resource merging.
*/


/*
	lock_guard + adopt_lock:
 - Used when you’ve already locked a mutex before creating lock_guard.
 - lock_guard just adopts ownership — no new locking happens.

	unique_lock + defer_lock:
 - Creates unique_lock without locking the mutex immediately.
 - You can lock it later when needed.
 - More flexible for conditional or timed locking.
*/