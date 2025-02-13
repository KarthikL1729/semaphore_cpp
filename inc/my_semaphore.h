// Implement semaphore using mutex and condition variable

#ifndef MY_SEMAPHORE_H
#define MY_SEMAPHORE_H

#include <iostream>
#include <mutex>
#include <condition_variable>

using namespace std;

class Semaphore {

    private:
    mutex mtx;
    condition_variable cv;  // Condition variable for waiting without busy waiting
    int count;  // Track available parking spots (resources)

    public:
    Semaphore(int count = 1) : count(count) {}

    void notify() {
        unique_lock lock(mtx);
        ++count;
        cv.notify_one();
    }

    void wait() {
        unique_lock lock(mtx);
        while (count == 0) {
            cv.wait(lock);
        }
        --count;
    }
    int get_count() {
        unique_lock lock(mtx);
        return count; 
    }
};

#endif //MY_SEMAPHORE_H