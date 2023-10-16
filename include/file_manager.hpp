#ifndef MULTITHREAD_LAB_FILE_MANAGER_HPP
#define MULTITHREAD_LAB_FILE_MANAGER_HPP

#include <ostream>

class file_manager {
public:
    explicit file_manager(const std::string& file) {
        if (!_file.is_open())
            _file.open(file, std::ios::app);
    }
    ~file_manager() {
        _file.close();
    }
    friend file_manager& operator<<(file_manager& file, const std::vector<std::string>& vector){
        for (auto& hash : vector) {
            file._file << hash << "\n";
        }
        return file;
    }

private:
    std::ofstream _file;
};

#endif //MULTITHREAD_LAB_FILE_MANAGER_HPP
