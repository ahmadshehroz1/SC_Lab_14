#include <iostream>
#include <deque>
#include <thread>
#include <vector>
#include <mutex>

// Shared data structure
std::deque<int> shared_list;
// Mutex to ensure thread safety
std::mutex mtx;

void modify_list() {
    for (int i = 0; i < 5; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // Ensure exclusive access to shared_list
        shared_list.push_back(i);
        std::cout << "Added " << i << " to the shared list" << std::endl;
    }
}

int main() {
    // Vector to hold threads
    std::vector<std::thread> threads;

    // Create and start 5 threads
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(modify_list);
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    // Print the final shared list
    std::cout << "Final shared list: ";
    for (int value : shared_list) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
