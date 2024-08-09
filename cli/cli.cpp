#include "picosha2.h"
#include <string>
#include <random>
#include <csignal>
#include <list>
#include "file_manager.hpp"
#include "thread_manager.hpp"
#include "thread_safe_queue.hpp"

static volatile sig_atomic_t flag = 0;

void signal_handler(int) {
    flag = 1;
}

std::string generate_source () {
    std::string source;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<> dist(1,1000);
    for (int i = 0; i < dist(rng); ++i) {
        source += (char)(rng());
    }
    return source;
}

std::string create_hash(const std::string& source) {
    std::string hash;
    picosha2::hash256_hex_string(source, hash);
    return hash;
}

bool check_if_valid (const std::string& hash) {
    return hash.substr(hash.length()-4,hash.length()) == "0000";
}

void gather_hashes (thread_safe_queue& queue) {
    while (true) {
        if (flag == 1){
            return;
        }
        std::string hash = create_hash(generate_source());
        if (check_if_valid(hash)) {
            queue.push(hash);
        }
    }
}

void write_in_file (file_manager& file, thread_safe_queue& queue) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        for (size_t i = 0; i < queue.get_queue().size(); ++i) {
            file.get_file() << queue.get_queue().front() << "\n";
            queue.pop();
        }
        if (flag == 1)
            return;
    }
}

int main (int argc, char** argv) {

    signal(SIGINT, signal_handler);

    size_t M;
    if (argc == 3) {
        M = std::stoi(argv[2]) - 1;
    }
    else {
        M = std::thread::hardware_concurrency() - 1;
    }

    std::string file_path = argv[1];
    file_manager file(file_path);

    thread_safe_queue queue;
    std::list<thread_manager> threads;

    thread_manager writing_thread (std::thread(write_in_file,std::ref(file),std::ref(queue)));
    for (int i = 0; i < M; ++i) {
        threads.emplace_back(std::thread(gather_hashes,std::ref(queue)));
    }
    return 0;
}