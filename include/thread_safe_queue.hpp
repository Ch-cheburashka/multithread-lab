#ifndef MULTITHREAD_LAB_THREAD_SAFE_QUEUE_HPP
#define MULTITHREAD_LAB_THREAD_SAFE_QUEUE_HPP

#include <queue>
#include <string>
#include <mutex>
#include <vector>

class thread_safe_queue {
public:
    void push(const std::string& value) {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.emplace_back(value);
    }

    std::vector<std::string> dump () {
        std::lock_guard<std::mutex> lock(_mutex);
        std::vector<std::string> hashes{_queue.begin(), _queue.end()};
        _queue.clear();
        return hashes;
    }
private:
    std::vector<std::string> _queue;
    std::mutex _mutex;
};

#endif //MULTITHREAD_LAB_THREAD_SAFE_QUEUE_HPP
