#ifndef MULTITHREAD_LAB_THREAD_SAFE_QUEUE_HPP
#define MULTITHREAD_LAB_THREAD_SAFE_QUEUE_HPP

#include <queue>
#include <string>
#include <mutex>

class thread_safe_queue {
public:
    void push(const std::string& value) {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.push(value);
    }
    void pop() {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.pop();
    }
    std::queue<std::string>& get_queue () {
        return _queue;
    }
private:
    std::queue<std::string> _queue;
    std::mutex _mutex;
};

#endif //MULTITHREAD_LAB_THREAD_SAFE_QUEUE_HPP
