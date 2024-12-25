#include <iostream>
#include <thread>

// Function to print numbers from 1 to 10
void print_numbers() {
    for (int i = 1; i <= 10; ++i) {
        std::cout << i << std::endl;
    }
}

// Function to print squares of numbers from 1 to 10
void print_squares() {
    for (int i = 1; i <= 10; ++i) {
        std::cout << i * i << std::endl;
    }
}

int main() {
    // Create threads
    std::thread thread1(print_numbers);
    std::thread thread2(print_squares);

    // Wait for both threads to finish
    thread1.join();
    thread2.join();

    return 0;
}
