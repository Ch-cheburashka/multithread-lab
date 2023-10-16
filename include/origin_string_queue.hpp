//
// Created by mrmamongo on 12.10.23.
//

#ifndef MULTITHREAD_LAB_ORIGIN_STRING_QUEUE_HPP
#define MULTITHREAD_LAB_ORIGIN_STRING_QUEUE_HPP
#include <string_view>
#include <string>
#include <vector>
#include <queue>
#include <mutex>

class origin_string_queue {
public:
    static origin_string_queue* get_instance(){
        static origin_string_queue instance{};
        return &instance;
    }

    void push(const std::string& value) {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.emplace(value);
        _condition.notify_one();
    }

    std::string pop() {
        std::unique_lock<std::mutex> lock(_mutex);
        std::string result;
        _condition.wait(lock, [this]{
            return !this->_queue.empty();
        });
        _queue.pop();
        return result;
    }

    origin_string_queue(const origin_string_queue&) = delete;
    origin_string_queue(origin_string_queue&&) = delete;
    origin_string_queue& operator=(const origin_string_queue&) = delete;
    origin_string_queue& operator=(origin_string_queue&) = delete;

private:
    origin_string_queue() = default;

    mutable std::mutex _mutex;
    std::condition_variable _condition;
    std::queue<std::string> _queue;
};


#endif //MULTITHREAD_LAB_ORIGIN_STRING_QUEUE_HPP
