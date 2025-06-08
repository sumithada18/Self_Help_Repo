//// deadlock avoidance 
//#include <iostream>
//#include <thread>
//#include <mutex>
//using namespace std::literals;
//
//std::mutex m1, m2;
//
//// A scoped lock is a C++17 feature designed to lock multiple mutexes safely 
//// and easily — and automatically unlock them when the scope ends(RAII).
//
//void taskA(){
//	std::cout << "taskA trying to lock \n";
//	std::scoped_lock scl(m1, m2);
//	std::cout << "taskA has locked mutexes m1 and m2 \n";
//	std::this_thread::sleep_for(50ms);
//	std::cout << "taskA releasing mutexes 1 and 2 \n";
//}
//
//void taskB(){
//	std::cout << "taskB trying to lock \n";
//	std::scoped_lock scl(m2, m1);
//	std::cout << "taskB has locked mutexes m1 and m2 \n";
//	std::this_thread::sleep_for(50ms);
//	std::cout << "taskB releasing mutexes 1 and 2 \n";
//}
//
//int main() {
//
//	std::thread t1(taskA);
//	std::thread t2(taskB);
//
//	t1.join();
//	t2.join();
//
//	return 0;
//}

/*
 difference between std::lock and std::scoped_lock : 

	std::lock																					std::scoped_lock
  - A function — locks multiple mutexes without deadlock, but you must unlock manually.		 - A class — locks multiple mutexes safely and unlocks automatically (RAII).
  - Needs defer_lock with unique_lock.														 - No need for defer_lock, it handles everything.
  - Example:																				 - Example:
    std::lock(m1, m2);																		   std::scoped_lock lock(m1, m2); — one-liner, safe and clean.
    then create unique_lock using adopt_lock.	
  - Available since C++11.																	 - Available since C++17.
*/