//#include <iostream>
//#include <thread>
//#include <mutex>
//using namespace std::literals;
//std::mutex mtx1;
//std::mutex mtx2;

//void taskA() {
//    std::lock_guard<std::mutex>lg1(mtx1);
//    std::this_thread::sleep_for(100ms);
//    std::lock_guard<std::mutex>lg2(mtx2);
//}
//
//void taskB() {
//    std::lock_guard<std::mutex>lg1(mtx2);
//    std::this_thread::sleep_for(100ms);
//    std::lock_guard<std::mutex>lg2(mtx1);
//}
//
//int main()
//{
//    std::thread thr(taskA);
//    std::thread thr2(taskB);
//
//    thr.join();
//    thr2.join();
//
//    return 0;
//}

/*
Time	    Thread A                                   	Thread B	                        Result
T0	  Starts and locks mtx1.	                Starts and locks mtx2.	                Both running fine.
T1	  Sleeps for 100ms (still holding mtx1).	Sleeps for 100ms (still holding mtx2).	Both waiting — locks held!
T2	  Wakes up and tries to lock mtx2.	        Wakes up and tries to lock mtx1.    	Both blocked waiting on each other.
T3	  mtx2 still held by Thread B.             	mtx1 still held by Thread A.	        Deadlock: both waiting forever.

*/

//void taskA() {
//    std::lock_guard<std::mutex>lg1(mtx1);
//    std::cout << "taskA \n";
//    std::this_thread::sleep_for(100ms);
//    std::lock_guard<std::mutex>lg2(mtx2);
//}
//
//void taskB() {
//    std::lock_guard<std::mutex>lg1(mtx1);
//    std::cout << "taskB \n";
//    std::this_thread::sleep_for(100ms);
//    std::lock_guard<std::mutex>lg2(mtx2);
//}

//int main()
//{
//    std::thread thr(taskA);
//    std::thread thr2(taskB);
//
//    thr.join();
//    thr2.join();
//
//    return 0;
//}

/*
Time	Thread A	        Thread B            	                State
T0	    Locks mtx1	       Tries to lock mtx1 (waits)   	Thread A active. Thread B waiting.
T1	    Locks mtx2	       Still waiting for mtx1	        Thread A progressing. Thread B waiting.
T2	    Unlocks both.     Locks mtx1 → mtx2	                Thread A finished. Thread B starts.
T3	        -	           Unlocks both.	                Both threads finish safely.

 Summary:
Consistent lock order = no deadlock!
*/

/*
  Condition	           Meaning (Simple)	                                        Result if Present
 Mutual Exclusion     Resource can be used by one thread at a time only.	     Threads must wait for resource.
 Hold and Wait	     Thread holds one resource & waits for another.	         Waiting loop starts.
 No Preemption	     Resource cannot be forcibly taken away from a thread.	 Threads hold resources indefinitely.
 Circular Wait	     Threads wait in a cycle for each other's resources.	 Infinite waiting — deadlock.
*/