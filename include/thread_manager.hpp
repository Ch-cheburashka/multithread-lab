#ifndef MULTITHREAD_LAB_THREAD_MANAGER_HPP
#define MULTITHREAD_LAB_THREAD_MANAGER_HPP

#include <thread>
#include <functional>


class thread_manager {
public:
    explicit thread_manager(std::thread&& thread) : _thread(std::move(thread)) {}

    thread_manager(const thread_manager&) = delete;
    thread_manager& operator=(const thread_manager&) = delete;

    thread_manager(thread_manager&& other) {
        _thread = std::move(other._thread);
    }

    ~thread_manager() {
        _thread.join();
    }
private:
    std::thread _thread;
};

#endif //MULTITHREAD_LAB_THREAD_MANAGER_HPP
