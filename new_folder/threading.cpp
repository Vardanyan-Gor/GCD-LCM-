#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

std::mutex mtx;
std::atomic<bool> stop_flag(false);
int counter = 0;

void worker_task() {
    while (!stop_flag.load()) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            counter += 2;
            std::cout << "[Worker]: Counter = " << counter << std::endl;
            if (counter > 50) {
                stop_flag.store(true);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void main_task() {
    while (!stop_flag.load()) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            counter += 1;
            std::cout << "[Main]: Counter = " << counter << std::endl;
            if (counter > 1000) {
                stop_flag.store(true);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

int main() {
    std::thread worker(worker_task);

    main_task();

    if (worker.joinable()) {
        worker.join();
    }

    std::cout << "Execution complete." << std::endl;
    return 0;
}
