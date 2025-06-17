Print/Odd Even 
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

int counter = 1;
const int MAX = 10;

std::mutex mtx;
std::condition_variable cv;
bool isEvenTurn = false;

void printOdd() {
    while (counter <= MAX) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !isEvenTurn; });

        if (counter <= MAX) {
            std::cout << "Odd: " << counter << "\n";
            counter++;
            isEvenTurn = true;
            cv.notify_one();
        }
    }
}

void printEven() {
    while (counter <= MAX) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return isEvenTurn; });

        if (counter <= MAX) {
            std::cout << "Even: " << counter << "\n";
            counter++;
            isEvenTurn = false;
            cv.notify_one();
        }
    }
}

int main() {
    std::thread t1(printOdd);
    std::thread t2(printEven);

    t1.join();
    t2.join();

    return 0;
}
you can solve the odd/even printing problem using std::atomic (e.g., std::atomic<bool> is_odd_turn;).

Issue Compared to Condition Variable (cv):
The main issue is busy-waiting (or spinning).
-> With std::atomic: The thread whose turn it isn't would have to repeatedly check the atomic flag in a 
   loop (e.g., while (is_odd_turn != my_turn) { /* do nothing or yield */ }). This loop consumes CPU cycles even though the thread isn't doing useful
   work. It's like constantly asking, "Is it my turn yet? Is it my turn yet?"
-> With std::condition_variable: The waiting thread calls cv.wait() and goes to sleep (blocks). It consumes virtually no CPU until it's notified by the
   other thread. It's like saying, "Wake me up when it's my turn."

In short: std::atomic leads to inefficient busy-waiting, while std::condition_variable allows for efficient blocking and yielding of the CPU. 
Condition variables are generally preferred when threads need to wait for a condition to become true that another thread will signal.


1. Why can't we use std::atomic alone to solve the odd-even thread problem?
✅ Answer:
Because std::atomic only ensures safe concurrent access to a variable — it does not allow threads to wait or sleep until a condition is met.
So, we'd still need to use busy waiting, which wastes CPU cycles. Atomic can't put a thread to sleep when it's not its turn.

2. Why is using only std::mutex (without condition_variable) not ideal here?
✅ Answer:
Using only mutex means the thread has to repeatedly lock, check, and unlock the mutex in a loop to see if it’s its turn — this is called busy waiting, which uses unnecessary CPU.
There’s no way to efficiently sleep and wait for the condition to change, which condition_variable provides.
