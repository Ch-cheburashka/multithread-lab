#ifndef MULTITHREAD_LAB_FILE_MANAGER_HPP
#define MULTITHREAD_LAB_FILE_MANAGER_HPP

#include <ostream>

class file_manager {
public:
    explicit file_manager(const std::string& file) {
        if (!_file.is_open())
            _file.open(file);
    }
    ~file_manager() {
        _file.close();
    }
    std::ofstream& get_file() {
        return _file;
    }
private:
    std::ofstream _file;
};

#endif //MULTITHREAD_LAB_FILE_MANAGER_HPP
