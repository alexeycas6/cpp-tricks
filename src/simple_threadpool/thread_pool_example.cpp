#include <iostream>
#include <string>
#include "thread_pool.hpp"

int main() {
    constexpr const int workers_count = 4;
    constexpr const int tasks_count = 10;
    constexpr const int total_tasks_count = 15;

    thread_pool pool(4);
    pool.start();
    for (int i = 0; i < tasks_count; i++)
        pool.push(task(std::string("task" + std::to_string(i))));

    using namespace std::chrono_literals;
    for (int i = 0; i < total_tasks_count - tasks_count; i++) {
        std::this_thread::sleep_for(1s);
        pool.push(task(std::string("task" + std::to_string(tasks_count + i))));
    }

    pool.stop(false);

    pool.push(task("rtrg"));

    return 0;
}