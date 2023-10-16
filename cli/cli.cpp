#include "picosha2.h"
#include <string>
#include <random>
#include <csignal>
#include <list>
#include "file_manager.hpp"
#include "thread_manager.hpp"
#include "thread_safe_queue.hpp"
#include "ThreadPool.hpp"
#include "origin_string_queue.hpp"
#include "hashed_string_queue.hpp"

static volatile sig_atomic_t flag = 0;

void signal_handler(int) {
    flag = 1;
}

void generate_source() {
    for (;;) {
        std::string source;
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<> dist(1, 1000);
        for (int i = 0; i < dist(rng); ++i) {
            source += (char) (rng());
        }
        origin_string_queue::get_instance()->push(source);
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(0.1ms);
    }
}

std::string create_hash(const std::string &source) {
    std::string hash;
    picosha2::hash256_hex_string(source, hash);
    return hash;
}

bool check_if_valid(const std::string &hash) {
    return hash.substr(hash.length() - 4, hash.length()) == "0000";
}

void gather_hashes() {
    for (;;) {
        std::string source = origin_string_queue::get_instance()->pop();
        std::string hash = create_hash(source);
        if (check_if_valid(hash)) {
            hashed_string_queue::get_instance()->push(hash);
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(0.1ms);
    }
}

void write_in_file(std::string file_path) {
    for (;;) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        file_manager file(file_path);
        file << hashed_string_queue::get_instance()->dump();
    }
}

int main(int argc, char **argv) {

    signal(SIGINT, signal_handler);
    // extract file_path from argv

    // ==========================
    size_t M;
    if (argc == 3) {
        M = std::stoi(argv[2]) - 1;
    } else {
        M = std::thread::hardware_concurrency() - 1;
    }

    std::string file_path = argv[1];

    ThreadPool thread_pool(M);

    thread_pool.enqueue(generate_source);
    thread_pool.enqueue(gather_hashes);
    thread_pool.enqueue(write_in_file,std::move(file_path));

    return 0;
}

/*
 * 1. Обработать в циклах флаг об остановке программы
 * 2. Продебажить и посмотреть, почему не генерируются хэши
 */