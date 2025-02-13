#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include "inc/my_semaphore.h"

#define TOTAL_SPOTS 10
#define TOTAL_CARS 20

using namespace std;

mutex cout_mtx; 

void car(int id, Semaphore& parking_lot) {
    
    parking_lot.wait(); // Acquire parking spot or wait
    
    // Parking successful
    cout_mtx.lock();
    cout << "Car " << id << " PARKED (free spots: " << parking_lot.get_count() << ")\n";
    cout_mtx.unlock();
    
    this_thread::sleep_for(chrono::seconds(2)); // Stay parked for 2 seconds
    
    parking_lot.notify(); // Release parking spot
    
    cout_mtx.lock();
    cout << "Car " << id << " LEFT (free spots: " << parking_lot.get_count() << ")\n";
    cout_mtx.unlock();
}

int main() {
    
    Semaphore parking_lot(TOTAL_SPOTS);
    
    vector<thread> cars;
    for(int i = 0; i < TOTAL_CARS; ++i) {
        cars.emplace_back(car, i, ref(parking_lot));
    }
    
    for(auto& t : cars) {
        t.join();
    }
    
    return 0;
}