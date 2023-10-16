cmake_minimum_required(VERSION 3.22)
project(multithread-lab)

set(CMAKE_CXX_STANDARD 20)


add_library(
        thread_manager INTERFACE
)

target_include_directories(thread_manager INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_subdirectory(third-party/picosha)

add_executable(cli cli/cli.cpp include/origin_string_queue.hpp)
target_link_libraries(cli thread_manager picosha2)