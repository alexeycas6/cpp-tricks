#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

class cache_invalidation {

private:
    std::condition_variable m_invalidation;
    std::chrono::seconds m_duration;

    std::mutex m_cache_lock;
    std::mutex m_cout_lock;

    std::jthread m_addition_thread;
    std::jthread m_invalidation_thread;

    std::vector<int> m_cache;

    void fill_cache() {
        while (true) {
            m_cache_lock.lock();
            for (int i = 0; i < 10; i++)
                m_cache.push_back(i);
            m_cache_lock.unlock();

            std::this_thread::sleep_for(200ms);
        }
    };

    void invalidate_cache() {

        while (true) {
            std::unique_lock<std::mutex> lock(m_cache_lock);
            m_invalidation.wait_for(lock, m_duration);
            auto tmp = m_cache.size();
            m_cache.clear();
            auto cache_size = m_cache.size();
            lock.unlock();

            std::lock_guard<std::mutex> lock_cout(m_cout_lock);
            std::cout << "cache clear, size: " << tmp << " -> " << cache_size
                      << std::endl;
        }
    }

public:
    cache_invalidation(std::chrono::seconds duration_sec)
        : m_duration { duration_sec } {};

    void start() {
        m_invalidation_thread
            = std::jthread(&cache_invalidation::invalidate_cache, this);

        m_addition_thread = std::jthread(&cache_invalidation::fill_cache, this);
    }
};
