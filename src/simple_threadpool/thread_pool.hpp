#pragma once

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class task {
    std::string m_name;

public:
    task() = default;

    task(std::string name)
        : m_name { name } { }

    std::string get_name() { return m_name; }

    void run_task() {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(3s);
    }
};

class thread_pool {
    mutable std::mutex m_mutex_queue;
    mutable std::mutex m_mutex_cout;

    std::queue<task> m_tasks;
    std::condition_variable m_condition;
    std::vector<std::thread> m_threads;
    unsigned m_workers_count;

    bool m_terminate_soft { false };
    bool m_terminate_immediately { false };
    bool m_allow_push { true };

    void run_task() noexcept {
        while (true) {
            if (m_terminate_soft && m_tasks.empty() || m_terminate_immediately)
                return;

            auto elem = pop_and_wait();
            m_mutex_cout.lock();
            std::cout << "starting " << elem->get_name() << " from thread "
                      << std::this_thread::get_id() << std::endl;
            m_mutex_cout.unlock();

            elem->run_task();

            m_mutex_cout.lock();
            std::cout << "finished " << elem->get_name() << std::endl;
            m_mutex_cout.unlock();
        }
    }

public:
    thread_pool() = default;
    thread_pool(unsigned workers_count)
        : m_workers_count { workers_count } {};
    thread_pool(const thread_pool& other) {
        std::lock_guard<std::mutex> lk(other.m_mutex_queue);
        m_tasks = other.m_tasks;
    };

    ~thread_pool() { stop(false); }

    void push(const task& task_) {
        if (m_allow_push) {
            std::lock_guard<std::mutex> lock(m_mutex_queue);
            m_tasks.push(task_);
            m_condition.notify_one();
        } else
            std::cout << "push not allowed" << std::endl;
    };

    std::shared_ptr<task> pop_and_wait() {
        // if condition not satisfied -> sleep, free mutex, push allowed
        std::unique_lock<std::mutex> lock(m_mutex_queue);
        m_condition.wait(lock, [this] { return !m_tasks.empty(); });

        auto res = std::make_shared<task>(m_tasks.front());
        m_tasks.pop();
        return res;
    }

    void start() {
        m_threads.reserve(m_workers_count);
        for (int i = 0; i < m_workers_count; i++)
            m_threads.emplace_back(&thread_pool::run_task, this);
    }

    void stop(bool stop_immediately) {
        std::unique_lock<std::mutex> lock(m_mutex_queue);
        if (stop_immediately)
            m_terminate_immediately = true;
        else
            m_terminate_soft = true;
        m_allow_push = false;
        lock.unlock();

        for (auto& active_thread : m_threads)
            if (active_thread.joinable())
                active_thread.join();

        m_threads.clear();
    };
};