# C++ Implementation of Semaphores using Mutex and Condition Variables

This is a simple implementation of semaphores using mutex and condition variables in C++. The semaphore class is implemented in `my_semaphore.h` and the test program is `parking_lot.cpp` which simulates a parking lot.

The semaphore works by using a mutex to protect updates of the `count` variable, which keeps track of the number of threads that can use the semaphore. The `wait` function decrements the count and if the count is equal to zero, the thread is blocked using a condition variable. The condition variable is used to eliminate busy waiting and to allow the thread to sleep until the count is greater than zero.

The `notify` function increments the count, it signals the condition variable to wake up a waiting thread, as a new slot opened up.

## The test program

The test program simulates a parking lot with a limited number of parking spaces (10 by default in the code). The parking lot is implemented as a semaphore with a count equal to the number of parking spaces. Each car is a thread that tries to enter the parking lot. If the parking lot is full, the car has to wait until a parking space becomes available. When a car leaves the parking lot, it signals the semaphore to allow another car to enter.

## Building and running the program

To build the program, run the following commands:

```bash
g++ -std=c++17 -pthread -fsanitize=thread parking_lot.cpp -o parking_lot
```

To run the program, execute the following command:

```bash
./parking_lot
```

The program will output the status of the parking lot as cars enter and leave the parking lot.

*Note:* All the programs were compiled using g++ version 13.3.0 on WSL with Ubuntu 24.04 and WSL2 kernel version 5.15.167.4. They have also been tested on Ubuntu 20.04 with g++ version 9.4.0 and kernel version 5.4.0-202-generic. `fsanitize` was used for checking thread safety, and is not necessary for normal compilation. The flag does not work with gcc version 9.4.0 as tested and should be removed in that case for compilation.

---