#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

std::mutex mtx;
std::atomic<bool> quit_program(false);
int global_counter = 0;

void my_async_thread() {
    while (!quit_program) {
        std::lock_guard<std::mutex> lock(mtx);
        global_counter += 2;
        if (global_counter > 50) {
            quit_program = true;
        }
        std::cout << "WorkerThread: " << global_counter << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void main_thread() {
    while (!quit_program) {
        std::lock_guard<std::mutex> lock(mtx);
        global_counter += 1;
        if (global_counter > 1000) {
            quit_program = true;
        }
        std::cout << "MainLoop: " << global_counter << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    std::thread worker(my_async_thread);

    main_thread();

    worker.join();

    std::cout << "Program finished." << std::endl;
    return 0;
}
