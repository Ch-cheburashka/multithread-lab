#include "../third-party/PicoSHA2-master/picosha2.h"
#include <string>
#include <random>
#include <csignal>
#include <list>
#include <mutex>
#include "file_manager.hpp"
#include "thread_manager.hpp"

static bool flag = false;

void signal_handler(int) {
    flag = true;
}

char generate_char () {
    std::random_device dev;
    std::mt19937 rng(dev());
    return (char)(rng());
}

std::string generate_source () {
    std::string source;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<> dist(1,1000);
    for (int i = 0; i < dist(rng); ++i) {
        source += generate_char();
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

void write_in_file (file_manager& file) {
    while (true) {
        if (flag)
            return;
        std::string hash = create_hash(generate_source());
        if (check_if_valid(hash)) {
            std::mutex mtx;
            std::lock_guard<std::mutex> lock(mtx);
            file.get_file() << hash << "\n";
        }
    }
}

int main (int argc, char** argv) {
    signal(SIGINT, signal_handler);

    size_t M;
    if (argc == 3) {
        M = std::stoi(argv[2]);
    }
    else {
        M = std::thread::hardware_concurrency();
    }

    std::string file_path = argv[1];
    file_manager file(file_path);

    std::list<thread_manager> threads;

    for (int i = 0; i < M; ++i) {
        threads.emplace_back(std::thread(write_in_file,std::ref(file)));
    }

    return 0;
}