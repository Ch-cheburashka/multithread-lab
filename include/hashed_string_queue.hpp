//
// Created by mrmamongo on 12.10.23.
//

#ifndef MULTITHREAD_LAB_HASHED_STRING_QUEUE_HPP
#define MULTITHREAD_LAB_HASHED_STRING_QUEUE_HPP
#include <string_view>
#include <string>
#include <vector>
#include <queue>
#include <mutex>

class hashed_string_queue {
public:
    static hashed_string_queue* get_instance(){
        static hashed_string_queue instance{};
        return &instance;
    }

    void push(const std::string& value) {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.emplace_back(value);
        _condition.notify_one();
    }

    std::vector<std::string> dump () {
        std::unique_lock<std::mutex> lock(_mutex);
        _condition.wait(lock, [this]{
            return !this->_queue.empty();
        });
        std::vector<std::string> hashes{_queue.begin(), _queue.end()};
        _queue.clear();
        return hashes;
    }

    hashed_string_queue(const hashed_string_queue&) = delete;
    hashed_string_queue(hashed_string_queue&&) = delete;
    hashed_string_queue& operator=(const hashed_string_queue&) = delete;
    hashed_string_queue& operator=(hashed_string_queue&) = delete;

private:
    hashed_string_queue() = default;

    mutable std::mutex _mutex;
    std::vector<std::string> _queue;
    std::condition_variable _condition;
};


#endif //MULTITHREAD_LAB_HASHED_STRING_QUEUE_HPP
