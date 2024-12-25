#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <ctime>

// Bank account class
class BankAccount {
private:
    int balance;
    std::mutex mtx; // Mutex for thread safety

public:
    BankAccount(int initial_balance = 0) : balance(initial_balance) {}

    // Deposit money into the account
    void deposit(int amount) {
        std::lock_guard<std::mutex> lock(mtx);
        balance += amount;
        std::cout << "Deposited " << amount << ", balance: " << balance << std::endl;
    }

    // Withdraw money from the account
    void withdraw(int amount) {
        std::lock_guard<std::mutex> lock(mtx);
        if (balance >= amount) {
            balance -= amount;
            std::cout << "Withdrew " << amount << ", balance: " << balance << std::endl;
        } else {
            std::cout << "Insufficient funds" << std::endl;
        }
    }

    // Get the final balance
    int get_balance() const {
        return balance;
    }
};

// Shared bank account instance
BankAccount account;

// Perform random transactions
void perform_transaction() {
    for (int i = 0; i < 10; ++i) {
        if (rand() % 2 == 0) {
            int amount = rand() % 41 + 10; // Random deposit amount between 10 and 50
            account.deposit(amount);
        } else {
            int amount = rand() % 41 + 10; // Random withdraw amount between 10 and 50
            account.withdraw(amount);
        }
    }
}

int main() {
    std::srand(std::time(0)); // Seed the random number generator

    // Create and start 5 threads
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(perform_transaction);
    }

    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }

    // Print the final balance
    std::cout << "Final balance: " << account.get_balance() << std::endl;

    return 0;
}
