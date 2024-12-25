#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

// Shared counter
int counter = 0;
// Mutex for synchronization
std::mutex mtx;

void increment_counter() {
    for (int i = 0; i < 100; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // Synchronize access to the shared counter
        ++counter;
    }
}

int main() {
    // Create a vector to hold threads
    std::vector<std::thread> threads;

    // Launch 3 threads
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(increment_counter);
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    // The final value of counter should be 300
    std::cout << "Final counter value: " << counter << std::endl;

    return 0;
}
